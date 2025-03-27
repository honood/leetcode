import json
import os
import logging
import argparse
from dataclasses import dataclass, field

logging.basicConfig(
    level=logging.INFO,
    format='%(levelname)s: %(message)s'
)

EXT_TO_LANG = {
    ".c": "C",
    ".cpp": "C++",
    ".cxx": "C++",
    ".cc": "C++",
    ".swift": "Swift",
    ".py": "Python",
    ".rb": "Ruby",
    ".rs": "Rust",
    ".go": "Go",
    ".zig": "Zig",
    ".js": "JavaScript",
    ".ts": "TypeScript",
    ".sql": "SQL"
}

LANG_TO_EXT = {
    "C": ".c",
    "C++": ".cpp",
    "Swift": ".swift",
    "Python": ".py",
    "Ruby": ".rb",
    "Rust": ".rs",
    "Go": ".go",
    "Zig": ".zig",
    "JavaScript": ".js",
    "TypeScript": ".ts",
    "SQL": ".sql"
}


@dataclass
class TopicTag:
    slug: str
    name: str


@dataclass
class Problem:
    index: int
    slug: str
    title: str
    difficulty: str
    topic_tags: list[TopicTag] = field(default_factory=list)


@dataclass
class Subgroup:
    name: str
    questions: list[Problem] = field(default_factory=list)


@dataclass
class StudyPlan:
    slug: str
    name: str
    description: str
    subgroups: list[Subgroup] = field(default_factory=list)


def read_data_file(json_file: str) -> StudyPlan:
    """
    Read and parse LeetCode study plan data from a JSON file.

    Args:
        json_file: Path to the JSON file containing study plan data

    Returns:
        StudyPlan: Parsed study plan object

    Raises:
        FileNotFoundError: If the specified file doesn't exist
        json.JSONDecodeError: If the file contains invalid JSON
        ValueError: If the JSON structure doesn't match expected format
    """
    try:
        with open(json_file, 'r', encoding='utf-8') as f:
            data = json.load(f)
    except json.JSONDecodeError as e:
        logging.error(f"Invalid JSON format in {json_file}: {e}")
        raise
    except FileNotFoundError:
        logging.error(f"File not found: {json_file}")
        raise

    try:
        plan_detail = data['props']['pageProps']['dehydratedState']['queries'][0]['state']['data']['studyPlanV2Detail']
        study_plan = StudyPlan(plan_detail['slug'], plan_detail['name'], plan_detail['description'])

        for subgroup_json in plan_detail['planSubGroups']:
            subgroup = Subgroup(subgroup_json['name'])

            for question in subgroup_json['questions']:
                problem = Problem(index=int(question['questionFrontendId']),
                                  slug=question['titleSlug'],
                                  title=question['title'],
                                  difficulty=question['difficulty'])

                for tag_json in question['topicTags']:
                    tag = TopicTag(tag_json['slug'], tag_json['name'])
                    problem.topic_tags.append(tag)

                subgroup.questions.append(problem)

            study_plan.subgroups.append(subgroup)
    except (KeyError, TypeError) as e:
        logging.error(f"Unexpected JSON structure in {json_file}: {e}")
        raise ValueError(f"Failed to parse study plan data: {e}")

    return study_plan


def generate_study_plan_url(study_plan_slug: str) -> str:
    """
    Generate the URL for a study plan.
    Args:
        study_plan_slug: Slug of the study plan
    Returns:
        str: URL for the study plan
    """
    return f"https://leetcode.com/studyplan/{study_plan_slug}/"


def generate_question_url(question_slug: str, study_plan_slug: str) -> str:
    """
    Generate the URL for a question in a study plan.
    Args:
        question_slug: Slug of the question
        study_plan_slug: Slug of the study plan
    Returns:
        str: URL for the question
    """
    return f"https://leetcode.com/problems/{question_slug}/?envType=study-plan-v2&envId={study_plan_slug}"


def format_description(study_plan_desc: str) -> str:
    """
    Format the description string by:
    1. Replacing Unicode escape sequences
    2. Converting line breaks to bullet points

    Args:
        study_plan_desc: Raw description string with escape sequences

    Returns:
        Formatted description with bullet points
    """
    # Decode Unicode escape sequences
    description = bytes(study_plan_desc, 'utf-8').decode('unicode_escape')

    # Normalize line breaks (convert \r\n to \n)
    description = description.replace('\r\n', '\n')

    # Split by line breaks and add bullet points
    lines = description.split('\n')
    formatted_lines = [f"- {line}" for line in lines if line.strip()]

    # Join with newlines
    return '\n'.join(formatted_lines)


def generate_file_stem(problem: Problem) -> str:
    """
    Generate a file stem (name without extension) for a problem.
    Args:
        problem: Problem object containing problem data
    Returns:
        str: File stem
    """
    return f"{problem.index:04d}-{problem.slug}"


def generate_file_content(problem: Problem, study_plan_slug: str, language: str) -> str:
    """
    Generate file content for a problem in the specified language.
    Args:
        problem: Problem object containing problem data
        study_plan_slug: Slug of the study plan
        language: Programming language for the solution
    Returns:
        str: File content for the specified language
    """
    header = [
        "HoNooD <honood@gmail.com>",
        "yyyy.MM.dd HH:mm",
        "",
        f"{problem.index}. {problem.title}",
        f"{generate_question_url(problem.slug, study_plan_slug)}"
    ]

    if language in ["Python", "Ruby"]:
        prefix = "# "
    elif language == "SQL":
        prefix = "-- "
    else:
        prefix = "// "

    content = "\n".join([f"{prefix}{line}" for line in header])

    if language == "C++":
        content += "\n\nauto __unsync_with_stdio = std::ios::sync_with_stdio(false);"
        content += "\nauto __uncin_tie = std::cin.tie(nullptr);"

    content += "\n"
    return content


def find_solution_files(solutions_dir: str, problem: Problem, reference_path: str) -> tuple[bool, list[tuple[str, str]]]:
    """
    Find solution files for a problem in the solutions directory.
    Args:
        solutions_dir: Absolute directory path where solution files are stored
        problem: Problem object containing problem data
        reference_path: Absolute path to a reference file for comparison
    Returns:
        tuple: (bool, list)
            - bool: True if any solution files exist, False otherwise
            - list: List of tuples (language_name, relative_path) for each existing solution file
    """
    # Check if solutions directory exists
    if not os.path.exists(solutions_dir) or not os.path.isdir(solutions_dir):
        return False, []

    file_stem = generate_file_stem(problem)
    found_solutions = []
    for ext in EXT_TO_LANG:
        file_path = os.path.join(solutions_dir, f"{file_stem}{ext}")
        if os.path.isfile(file_path):
            language_name = EXT_TO_LANG[ext]
            relative_path = os.path.relpath(file_path, os.path.dirname(reference_path))
            found_solutions.append((language_name, relative_path))
    if found_solutions:
        return True, found_solutions
    else:
        return False, []


def generate_study_plan_markdown(study_plan: StudyPlan, solutions_dir: str, markdown_file_path: str) -> str:
    """
    Generate markdown content for a study plan.
    Args:
        study_plan: StudyPlan object containing study plan data
        solutions_dir: Absolute directory path where solution files are stored
        markdown_file_path: Absolute path to use as reference for calculating relative paths to solution files
    Returns:
        str: Markdown content for the study plan
    """
    markdown = f"## [{study_plan.name}]({generate_study_plan_url(study_plan.slug)})\n\n"
    markdown += f"{format_description(study_plan.description)}\n\n"
    for subgroup in study_plan.subgroups:
        markdown += f"### {subgroup.name}\n\n"
        for i, problem in enumerate(subgroup.questions, 1):
            problem_url = generate_question_url(problem.slug, study_plan.slug)
            problem_line = f"{i}. [{problem.index}\\. {problem.title}]({problem_url}) [{problem.difficulty}]"

            # Find solution files for the problem
            solutions_exist, solutions = find_solution_files(solutions_dir, problem, markdown_file_path)
            if solutions_exist:
                problem_line += " ("
                for j, (language_name, relative_path) in enumerate(solutions):
                    if j > 0:
                        problem_line += ", "
                    problem_line += f"[{language_name}]({relative_path})"
                problem_line += ")"
            problem_line += "\n"

            markdown += problem_line
        markdown += "\n"
    return markdown


def parse_arguments():
    """Parse command line arguments"""
    parser = argparse.ArgumentParser(description='Process LeetCode study plan data')

    parent_parser = argparse.ArgumentParser(add_help=False)
    parent_parser.add_argument('json_path', nargs='?', default=None,
                               help='JSON file name or path (default: data.json in current directory)')
    parent_parser.add_argument('--json-file', '-j', dest='named_json_path',
                               help='JSON file name or path (positional argument takes precedence)')

    subparsers = parser.add_subparsers(dest='command', help='Commands')

    markdown_parser = subparsers.add_parser('gen-markdown',
                                            help='Generate markdown from study pand data',
                                            parents=[parent_parser])
    markdown_parser.add_argument('--solutions-dir', '-s', dest='solutions_dir',
                                 help='Directory where solution files are stored (will not be created or modified)')
    markdown_parser.add_argument('--markdown-file', '-m', dest='markdown_file_path', required=True,
                                 help='Markdown file path used as reference for relative paths')

    solutions_parser = subparsers.add_parser('gen-sol-tmpls',
                                             help='Generate solution template files',
                                             parents=[parent_parser])
    solutions_parser.add_argument('--solutions-dir', '-s', dest='solutions_dir',
                                  help='Directory where solution files will be created (will be created if not exists)')
    solutions_parser.add_argument('--languages', '-l', dest='languages',
                                  choices=list(LANG_TO_EXT.keys()),
                                  nargs='+',
                                  help='Programming languages for solution templates (can specify multiple)')

    parser.add_argument('--usage', action='store_true',
                        help='Show usage examples and more information')

    return parser.parse_args()


def show_usage():
    """Display detailed usage information"""
    print("Usage Information:")
    print("  This script processes LeetCode study plan data from JSON files.")
    print("\nCommands:")
    print("  gen-markdown    Generate markdown from study plan data")
    print("  gen-sol-tmpls   Generate solution template files")
    print("\nExamples:")
    print("  python process_data.py gen-markdown data.json --markdown-file ../README.md --solutions-dir ../solutions")
    print("  python process_data.py gen-sol-tmpls data.json --languages C++ Go --solutions-dir ../solutions")
    print("\nOutput:")
    print("  The script generates markdown content and creates solution template files")


def normalize_path(path: str) -> str:
    """
    Normalize a path by expanding user home directory and converting to absolute path.
    Args:
        path: Path to normalize
    Returns:
        str: Normalized path
    """
    path = os.path.expanduser(path)
    if not os.path.isabs(path):
        path = os.path.join(os.getcwd(), path)
    path = os.path.normpath(path)
    return path


def main():
    args = parse_arguments()

    if args.usage:
        show_usage()
        return

    # Check if a command is specified
    if not hasattr(args, 'command') or args.command is None:
        logging.error("No command specified. Use --help for usage information.")
        return

    # Determine JSON file path, prioritizing positional argument
    if args.json_path is not None:
        json_file = args.json_path
    elif args.named_json_path is not None:
        json_file = args.named_json_path
    else:
        json_file = 'data.json'

    json_file = normalize_path(json_file)
    if not os.path.isfile(json_file):
        logging.error(f"JSON file not found: {json_file}")
        return

    # Process solutions directory
    if hasattr(args, 'solutions_dir') and args.solutions_dir is not None:
        solutions_dir = args.solutions_dir
    else:
        solutions_dir = 'solutions'

    solutions_dir = normalize_path(solutions_dir)
    # Check if solutions directory exists and is a directory
    if os.path.exists(solutions_dir) and not os.path.isdir(solutions_dir):
        logging.error(f"Solutions directory is not a directory: {solutions_dir}")
        return

    # Create solutions directory if needed for gen-sol-tmpls command
    if args.command == 'gen-sol-tmpls' and not os.path.exists(solutions_dir):
        try:
            os.makedirs(solutions_dir, exist_ok=True)
            logging.info(f"Created solutions directory: {solutions_dir}")
        except OSError as e:
            logging.error(f"Failed to create solutions directory: {e}")
            return

    try:
        study_plan = read_data_file(json_file)

        if args.command == 'gen-markdown':
            # Process markdown file path
            markdown_file = args.markdown_file_path
            markdown_file = normalize_path(markdown_file)
            markdown_content = generate_study_plan_markdown(study_plan, solutions_dir, markdown_file)
            print(markdown_content, end='')
            logging.info(f"Markdown content generated and printed to stdout")
        elif args.command == 'gen-sol-tmpls':
            # Determine language for solution templates
            languages = args.languages if hasattr(args, 'languages') and args.languages else ['C++']

            # Generate solution template files
            total_count = 0
            for language in languages:
                count = 0
                for subgroup in study_plan.subgroups:
                    for problem in subgroup.questions:
                        file_stem = generate_file_stem(problem)
                        file_ext = LANG_TO_EXT[language]
                        file_path = os.path.join(solutions_dir, f"{file_stem}{file_ext}")
                        if os.path.exists(file_path):
                            continue

                        content = generate_file_content(problem, study_plan.slug, language)
                        with open(file_path, 'w', encoding='utf-8') as f:
                            f.write(content)
                        logging.info(f"Created solution file: {file_path}")
                        count += 1

                logging.info(f"Created {count} solution template files for {language} in {solutions_dir}")
                total_count += count

            if len(languages) > 1:
                logging.info(f"Total: Created {total_count} solution template files in {solutions_dir}")
    except (FileNotFoundError, json.JSONDecodeError, ValueError) as e:
        logging.error(f"Failed to process JSON file: {e}")
        return


if __name__ == "__main__":
    main()
