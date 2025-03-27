# LeetCode Study Plan Data Extraction Guide

This guide provides two methods to extract data from LeetCode study plans.

## Method 1: Using JavaScript Console

1. Open one of the following pages in Google Chrome:
   - [LeetCode 75](https://leetcode.com/studyplan/leetcode-75/)
   - [Top Interview 150](https://leetcode.com/studyplan/top-interview-150/)
   - [Top 100 Liked](https://leetcode.com/studyplan/top-100-liked/)
   - [SQL 50](https://leetcode.com/studyplan/top-sql-50/)
2. After the page is fully loaded, open the JavaScript Console (View > Developer > JavaScript Console or press Cmd+Option+J), then copy and run the following JavaScript script:
    ```js
    (function() {
      function copyToClipboard(text) {
        try {
          // Create temporary textarea element
          const textarea = document.createElement('textarea');
          textarea.value = text;
          textarea.setAttribute('readonly', '');
          textarea.style.position = 'absolute';
          textarea.style.left = '-9999px';
          document.body.appendChild(textarea);
    
          // Select and copy text
          textarea.select();
          const success = document.execCommand('copy');
    
          // Remove temporary element
          document.body.removeChild(textarea);
    
          if (success) {
            console.log('✅ Content successfully copied to clipboard');
            return true;
          } else {
            console.warn('⚠️ Copy command was unsuccessful');
            return false;
          }
        } catch (err) {
          console.error('Error copying to clipboard:', err);
          return false;
        }
      }
    
      try {
        // Get __NEXT_DATA__ element
        const nextDataElement = document.getElementById('__NEXT_DATA__');
    
        if (!nextDataElement) {
          console.error('Could not find __NEXT_DATA__ element');
          return;
        }
    
        // Get JSON content
        const jsonContent = nextDataElement.textContent;
    
        // Parse and format JSON
        const parsedData = JSON.parse(jsonContent);
        const formattedJson = JSON.stringify(parsedData, null, 2);
    
        // Print formatted JSON to console
        console.log('Formatted JSON data:');
        console.log(formattedJson);
        console.log(`📊 Data size: ${(jsonContent.length / 1024).toFixed(2)} KB`);
    
        // Copy formatted JSON to clipboard
        if (copyToClipboard(formattedJson)) {
          console.log('You can now paste the formatted JSON data wherever needed');
        } else {
          console.log('Please manually copy the JSON data from the console');
        }
      } catch (error) {
        console.error('Error processing data:', error);
      }
    })();
    ```
3. After the script executes, the formatted JSON data will be printed to the JavaScript console and copied to your system clipboard.
4. Save the JSON data to a file.

## Method 2: Manual Extraction

This is a completely manual approach. Using [LeetCode 75](https://leetcode.com/studyplan/leetcode-75/) as an example:

### Extracting LeetCode 75 Study Plan Data

To extract the data for the LeetCode 75 study plan:

1. Open [LeetCode 75](https://leetcode.com/studyplan/leetcode-75/) in Google Chrome
2. Open Developer Tools (View > Developer > Developer Tools or press Cmd+Option+I)
3. Navigate to the Sources tab
4. In the Page navigation panel, locate and open the file at `top/leetcode.com/studyplan/leetcode-75/leetcode-75/`
5. Search for a script tag with the ID `__NEXT_DATA__`
6. Copy all the JSON content from this tag and save it to a file named `data.json`

This JSON contains the structured data for the LeetCode 75 study plan that can be parsed programmatically.

The same approach can be applied to other study plans such as [Top Interview 150](https://leetcode.com/studyplan/top-interview-150/), [Top 100 Liked](https://leetcode.com/studyplan/top-100-liked/), and [SQL 50](https://leetcode.com/studyplan/top-sql-50/).
