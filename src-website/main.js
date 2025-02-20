

// Function to simulate input() in JavaScript
function input(promptText) {
    // Display the prompt and get user input
    return prompt(promptText);
}


// Function to initialize the page and create UI elements dynamically
async function init() {
    try {
        // Fetch the instructions file from GitHub
        const response = await fetch('https://raw.githubusercontent.com/TheMaster1127/HTVM/refs/heads/main/HTVM-instructions-VERY-SIMPLE-DOCS.txt');
        if (!response.ok) throw new Error('Failed to load instructions file');
        
        // Get the file content and split into lines
        const text = await response.text();
        const lines = text.split('\n').filter(line => line.trim() !== ''); // Ignore empty lines
        
        // Set dark mode styles
        document.body.style.backgroundColor = '#121212'; // Dark background
        document.body.style.color = 'white'; // White text color
        document.body.style.fontFamily = 'Arial, sans-serif'; // Use a clean font
        document.body.style.margin = '0';
        document.body.style.padding = '0';
        
        // Create a wrapper div for editboxes
        const wrapperDiv = document.createElement('div');
        wrapperDiv.style.margin = '20px';
        wrapperDiv.style.padding = '20px';
        wrapperDiv.style.border = '1px solid #444'; // Dark border
        wrapperDiv.style.backgroundColor = '#1E1E1E'; // Darker background for the wrapper
        wrapperDiv.style.borderRadius = '8px';
        document.body.appendChild(wrapperDiv);
        // Create a container div to hold the editboxes
        const containerDiv = document.createElement('div');
        containerDiv.classList.add('input-container');
        wrapperDiv.appendChild(containerDiv);
        // Create an editbox for each line
        lines.forEach((line, index) => {
            // Create a div to hold both label and input
            const editBoxWrapper = document.createElement('div');
            editBoxWrapper.style.display = 'flex';
            editBoxWrapper.style.flexDirection = 'column'; // Stack label and input vertically
            editBoxWrapper.style.marginBottom = '20px'; // Space between each group
            containerDiv.appendChild(editBoxWrapper);
            // Create label
            const label = document.createElement('label');
            label.innerText = line;
            label.style.color = 'white'; // White label text
            label.style.marginBottom = '8px'; // Space between label and input
            editBoxWrapper.appendChild(label);
            // Create input (editbox)
            const editBox = document.createElement('input');
            editBox.type = 'text';
            editBox.name = line;  // Use line content as the name
            editBox.placeholder = `Enter ${line}`;
            editBox.style.width = '95%';
            editBox.style.padding = '12px';
            editBox.style.border = '1px solid #555'; // Dark border for inputs
            editBox.style.borderRadius = '4px';
            editBox.style.backgroundColor = '#333'; // Dark background for input boxes
            editBox.style.color = 'white'; // White text in input boxes
            editBox.style.fontSize = '16px'; // Font size for input
            editBoxWrapper.appendChild(editBox);
        });
        // Add a button to capture input values
        const actionButton = document.createElement('button');
        actionButton.innerText = 'Build';
        actionButton.style.padding = '12px 20px';
        actionButton.style.backgroundColor = '#6200EE'; // Purple button
        actionButton.style.color = 'white';
        actionButton.style.border = 'none';
        actionButton.style.borderRadius = '4px';
        actionButton.style.cursor = 'pointer';
        actionButton.style.display = 'block';
        actionButton.style.marginTop = '20px';
        actionButton.style.fontSize = '16px';
        actionButton.addEventListener('click', () => {
            collectInputs();
        });
        wrapperDiv.appendChild(actionButton);
    } catch (error) {
        console.error('Error initializing page:', error);
    }
}
// Function to collect inputs from all editboxes and call handleError
function collectInputs() {
    const inputs = document.querySelectorAll('input[type="text"]');
    let collectedData = '';
    inputs.forEach(input => {
        collectedData += input.value + '\n';  // Add each input value on a new line
    });
    try {
    // Pass the collected data to the handleError function in HTVM syntax
    const result = handleError(collectedData.trim());  // Call handleError with the input as a single string
    
    console.log('Result from handleError:\n' + result);
    
        if (result == "noERROR") {
        // If no errors, call afterBuild function
        afterBuild();
        }
    
    }
    catch (error)
    {
    alert(error)
    }
    
}
// Function called after the build if no errors are found
function afterBuild() {
    alert('Build completed successfully!');
    // You can add more actions here, like processing the results or saving them
}
// Initialize on page load
window.onload = init;
