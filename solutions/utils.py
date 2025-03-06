import json
import os
import logging
from datetime import datetime
from pathlib import Path
from dataclasses import dataclass

# 配置日志
logging.basicConfig(
    level=logging.INFO,
    format='%(levelname)s: %(message)s'
)


@dataclass
class Problem:
    """问题信息结构"""
    number: int
    title: str
    title_slug: str


def read_problems(json_file: str) -> list[Problem]:
    """从JSON文件中读取问题信息"""
    try:
        with open(json_file, 'r', encoding='utf-8') as f:
            data = json.load(f)
    except json.JSONDecodeError as e:
        logging.error(f"Invalid JSON format in {json_file}: {e}")
        return []
    except FileNotFoundError:
        logging.error(f"File not found: {json_file}")
        return []

    problems = []
    try:
        groups = (data['props']['pageProps']['dehydratedState']
        ['queries'][0]['state']['data']['studyPlanV2Detail']['planSubGroups'])

        for group in groups:
            for q in group['questions']:
                problems.append(Problem(
                    number=int(q['questionFrontendId']),
                    title=q['title'],
                    title_slug=q['titleSlug']
                ))
    except (KeyError, TypeError) as e:
        logging.error(f"Unexpected JSON structure in {json_file}: {e}")
        return []

    return problems


def generate_file_name(problem: Problem) -> str:
    """生成文件名"""
    return f"{problem.number:04d}-{problem.title_slug}.cpp"


def generate_file_content(problem: Problem,
                          url_template: str = "https://leetcode.com/problems/{}/?envType=study-plan-v2&envId=leetcode-75") -> str:
    current_time = datetime.now().strftime("%Y.%m.%d %H:%M")
    url = url_template.format(problem.title_slug)

    return f"""// HoNooD <honood@gmail.com>
// {current_time}

// {problem.number}. {problem.title}
// {url}

auto __unsync_with_stdio = std::ios::sync_with_stdio(false);
auto __uncin_tie = std::cin.tie(nullptr);
"""


def process_problems(json_file: str, directory: str):
    problems = read_problems(json_file)
    dir_path = Path(directory)

    if not dir_path.exists():
        logging.error(f"Directory '{directory}' does not exist")
        return

    for problem in problems:
        file_name = generate_file_name(problem)
        file_path = dir_path / file_name

        if file_path.exists():
            logging.warning(f"File already exists: {file_path}")
        else:
            try:
                with open(file_path, 'w', encoding='utf-8') as f:
                    f.write(generate_file_content(problem))
                logging.info(f"Created file: {file_path}")
            except IOError as e:
                logging.error(f"Failed to write file {file_path}: {e}")


def main():
    # 假设 questions.json 和要生成的文件在当前目录
    current_dir = os.getcwd()
    json_file = os.path.join(current_dir, "questions.json")

    if not os.path.exists(json_file):
        logging.error(f"JSON file not found: {json_file}")
        return

    process_problems(json_file, current_dir)


if __name__ == "__main__":
    main()
