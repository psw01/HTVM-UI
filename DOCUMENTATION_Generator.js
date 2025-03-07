

function LoopParseFunc(varString, delimiter1="", delimiter2="") {
    let items;
    if (!delimiter1 && !delimiter2) {
        // If no delimiters are provided, return an array of characters
        items = [...varString];
    } else {
        // Construct the regular expression pattern for splitting the string
        let pattern = new RegExp('[' + delimiter1.replace(/[.*+?^${}()|[\]\\]/g, '\\$&') + delimiter2.replace(/[.*+?^${}()|[\]\\]/g, '\\$&') + ']+');
        // Split the string using the constructed pattern
        items = varString.split(pattern);
    }
    return items;
}

function print(value) {
    console.log(value)
}

// Convert value to string
function STR(value) {
    if (value === null || value === undefined) {
        return ""; // Return a string for null or undefined
    } else if (typeof value === 'number') {
        return value.toString();
    } else if (typeof value === 'boolean') {
        return value ? "1" : "0";
    } else if (typeof value === 'string') {
        return value; // Return the string as is
    } else {
        // Handle any unexpected types gracefully
        return String(value); // Convert any other type to a string
    }
}

function Chr(number) {
    // Return the character corresponding to the Unicode code point, or an empty string if out of range
    return (number >= 0 && number <= 0x10FFFF) ? String.fromCharCode(number) : "";
}

function SubStr(str, startPos, length = -1) {
    // If str is null or undefined, return an empty string
    if (str === null || str === undefined) {
        return "";
    }
    let strLen = str.length;
    
    // Handle negative starting positions (C++ style)
    if (startPos < 1) {
        startPos = strLen + startPos;
        if (startPos < 0) startPos = 0;
    } else {
        startPos -= 1; // Convert to 0-based index (C++ style)
    }
    // Handle length (C++ style)
    if (length < 0) {
        length = strLen - startPos; // Length to end of string
    } else if (startPos + length > strLen) {
        length = strLen - startPos; // Adjust length to fit within the string
    }
    // Extract the substring
    return str.substr(startPos, length);
}

function Trim(inputString) {
    return inputString ? inputString.trim() : "";
}

function StrReplace(originalString, find, replaceWith) {
    return originalString.split(find).join(replaceWith);
}

function StrLower(string) {
    return string.toLowerCase();
}

function StrSplit(inputStr, delimiter, num) {
    const parts = inputStr.split(delimiter);
    return (num > 0 && num <= parts.length) ? parts[num - 1] : "";
}

// Function to sort and remove duplicates
function sortArr(inputArray) {
    // Remove duplicates using Set and sort the array
    return [...new Set(inputArray)].sort();
}

function countChars(string, theChar) {
    let count = 0;
    for (let char of string) {
        if (char === theChar) {
            count++;
        }
    }
    return count;
}

function StrTitleCase(inputString) {
    return inputString.split(' ')  // Split the string into words
        .map(word => {
            if (word) {  // Avoid empty words (multiple spaces)
                return word.charAt(0).toUpperCase() + word.slice(1).toLowerCase();  // Capitalize first letter
            }
            return word;  // If it's an empty string (spaces), keep it as is
        })
        .join(' ');  // Join the words back together with spaces
}

function HTVM_getLang_HTVM() {
    return "js";
}

function HTVM_Append(arr, value) {
    arr.push(value);
}

function HTVM_Size(arr) {
    return arr.length;
}


var instructionFileData = "";
var DOCS_params = "";
var DOCS_param1 = "";
var DOCS_param2 = "";
var DOCS_checkIfFuncNameExists = 0;
var OUTdocs_HTML = "";
var OUTdocs_MD = "";
function genDocs(mode) {
    var outDocs = "";
    if (Trim(instructionFileData) == "") {
        throw new Error("instructionFileData is empty");
        return "error: instructionFileData is empty!!!";
    }
    var inFunc = 0;
    let funcData_lang = [];
    let funcData_name = [];
    let funcData_desc = [];
    items1 = LoopParseFunc(instructionFileData, "\n", "\r")
    for (let A_Index1 = 0; A_Index1 < items1.length + 0; A_Index1++) {
        const A_LoopField1 = items1[A_Index1 - 0];
        if (Trim(A_LoopField1) == "funcEND======================funcEND==============") {
            inFunc = 0;
        }
        if (inFunc == 1) {
            if (SubStr(Trim(A_LoopField1), 1, 6) == "lang: ") {
                HTVM_Append(funcData_lang, Trim(A_LoopField1));
            }
            else if (SubStr(Trim(A_LoopField1), 1, 6) == "name: ") {
                HTVM_Append(funcData_name, Trim(A_LoopField1));
            }
            else if (SubStr(Trim(A_LoopField1), 1, 13) == "description: ") {
                HTVM_Append(funcData_desc, Trim(A_LoopField1));
            }
        }
        if (Trim(A_LoopField1) == "func======================func==============") {
            inFunc = 1;
        }
    }
    let allFuncNames = [sortArr(funcData_name)];
    var theFuncThatExistsIsCalled = "";
    if (DOCS_checkIfFuncNameExists == 1) {
        var exitedLoopCheckIfFuncNameExists = 0;
        for (let A_Index2 = 0; A_Index2 < HTVM_Size(allFuncNames) + 0; A_Index2++) {
            print(allFuncNames[A_Index2]);
            if (StrLower(DOCS_param2) == StrLower(Trim(StrSplit(allFuncNames[A_Index2], ":", 2)))) {
                theFuncThatExistsIsCalled = Trim(StrSplit(allFuncNames[A_Index2], ":", 2));
                exitedLoopCheckIfFuncNameExists = 1;
                break;
            }
        }
        if (exitedLoopCheckIfFuncNameExists == 1) {
            print("the func alredy exists!!! called: " + theFuncThatExistsIsCalled);
            ExitApp();
        } else {
            print("the func dosent exists!!! YOU CAN USE IT");
            ExitApp();
        }
    }
    // allFuncNames
    var allFuncNamesTemp = "";
    var tempDesc = "";
    var tempLang = "";
    for (let A_Index3 = 0; A_Index3 < HTVM_Size(funcData_name) + 0; A_Index3++) {
        //print(funcData_name[A_Index3])
        allFuncNamesTemp = funcData_name[A_Index3];
        tempLang = funcData_lang[A_Index3];
        tempDesc = funcData_desc[A_Index3];
        for (let A_Index4 = 0; A_Index4 < HTVM_Size(allFuncNames) + 0; A_Index4++) {
            if (Trim(allFuncNamesTemp) == Trim(StrSplit(allFuncNames[A_Index4], "|", 1))) {
                if (countChars(allFuncNames[A_Index4], "|") == 0) {
                    allFuncNames[A_Index4] = allFuncNames[A_Index4] + "|" + Trim(tempDesc) + "|" + Trim(tempLang);
                } else {
                    allFuncNames[A_Index4] = allFuncNames[A_Index4] + "|" + Trim(tempLang);
                }
            }
        }
    }
    let allFuncs = [];
    var tempstr = "";
    var isLangCpp = "";
    var isLangPy = "";
    var isLangJs = "";
    var isLangGo = "";
    var isLangLua = "";
    var isLangCs = "";
    var isLangJava = "";
    var isLangKotlin = "";
    var isLangRuby = "";
    var isLangNim = "";
    var isLangAhk = "";
    var isLangSwift = "";
    var isLangDart = "";
    var isLangTs = "";
    var isLangGroovy = "";
    var allFuncsTempAdd = "";
    var isDescNull = 0;
    for (let A_Index5 = 0; A_Index5 < HTVM_Size(allFuncNames) + 0; A_Index5++) {
        //print(allFuncNames[A_Index5])
        tempstr = Trim(allFuncNames[A_Index5]);
        isDescNull = 0;
        allFuncsTempAdd = "";
        isLangCpp = "No";
        isLangPy = "No";
        isLangJs = "No";
        isLangGo = "No";
        isLangLua = "No";
        isLangCs = "No";
        isLangJava = "No";
        isLangKotlin = "No";
        isLangRuby = "No";
        isLangNim = "No";
        isLangAhk = "No";
        isLangSwift = "No";
        isLangDart = "No";
        isLangTs = "No";
        isLangGroovy = "No";
        items6 = LoopParseFunc(tempstr, "|")
        for (let A_Index6 = 0; A_Index6 < items6.length + 0; A_Index6++) {
            const A_LoopField6 = items6[A_Index6 - 0];
            if (SubStr(Trim(A_LoopField6), 1, 8) == "lang: js") {
                isLangJs = "Yes";
            }
            else if (SubStr(Trim(A_LoopField6), 1, 8) == "lang: py") {
                isLangPy = "Yes";
            }
            else if (SubStr(Trim(A_LoopField6), 1, 9) == "lang: cpp") {
                isLangCpp = "Yes";
            }
            else if (SubStr(Trim(A_LoopField6), 1, 8) == "lang: go") {
                isLangGo = "Yes";
            }
            else if (SubStr(Trim(A_LoopField6), 1, 9) == "lang: lua") {
                isLangLua = "Yes";
            }
            else if (SubStr(Trim(A_LoopField6), 1, 8) == "lang: cs") {
                isLangCs = "Yes";
            }
            else if (SubStr(Trim(A_LoopField6), 1, 10) == "lang: java") {
                isLangJava = "Yes";
            }
            else if (SubStr(Trim(A_LoopField6), 1, 12) == "lang: kotlin") {
                isLangKotlin = "Yes";
            }
            else if (SubStr(Trim(A_LoopField6), 1, 10) == "lang: ruby") {
                isLangRuby = "Yes";
            }
            else if (SubStr(Trim(A_LoopField6), 1, 9) == "lang: nim") {
                isLangNim = "Yes";
            }
            else if (SubStr(Trim(A_LoopField6), 1, 9) == "lang: ahk") {
                isLangAhk = "Yes";
            }
            else if (SubStr(Trim(A_LoopField6), 1, 11) == "lang: swift") {
                isLangSwift = "Yes";
            }
            else if (SubStr(Trim(A_LoopField6), 1, 10) == "lang: dart") {
                isLangDart = "Yes";
            }
            else if (SubStr(Trim(A_LoopField6), 1, 8) == "lang: ts") {
                isLangTs = "Yes";
            }
            else if (SubStr(Trim(A_LoopField6), 1, 12) == "lang: groovy") {
                isLangGroovy = "Yes";
            }
            else if (SubStr(Trim(A_LoopField6), 1, 6) == "name: ") {
                allFuncsTempAdd += Trim(A_LoopField6) + "|";
            }
            else if (SubStr(Trim(A_LoopField6), 1, 13) == "description: ") {
                allFuncsTempAdd += Trim(A_LoopField6) + "|";
            }
            if (Trim(StrLower(A_LoopField6)) == "description: null") {
                isDescNull = 1;
            }
        }
        if (isDescNull != 1) {
            allFuncsTempAdd += isLangCpp + "|" + isLangPy + "|" + isLangJs + "|" + isLangGo + "|" + isLangLua + "|" + isLangCs + "|" + isLangJava + "|" + isLangKotlin + "|" + isLangRuby + "|" + isLangNim + "|" + isLangAhk + "|" + isLangSwift + "|" + isLangDart + "|" + isLangTs + "|" + isLangGroovy;
            HTVM_Append(allFuncs, allFuncsTempAdd);
        }
    }
    for (let A_Index7 = 0; A_Index7 < 20 + 0; A_Index7++) {
        //print("===========================================")
    }
    let categories = [];
    var theCurrentLine = "";
    var theCurrentDescCategory = "";
    var once = 0;
    var didWeFindSameCategory = 0;
    for (let A_Index8 = 0; A_Index8 < HTVM_Size(allFuncs) + 0; A_Index8++) {
        //print(allFuncs[A_Index8])
        once++;
        theCurrentLine = Trim(allFuncs[A_Index8]);
        theCurrentDescCategory = Trim(StrSplit(theCurrentLine, "|", 2));
        theCurrentDescCategory = Trim(StrSplit(theCurrentDescCategory, ":", 2));
        theCurrentDescCategory = Trim(StrLower(Trim(StrSplit(theCurrentDescCategory, "~~~", 1))));
        didWeFindSameCategory = 0;
        if (once == 1) {
            HTVM_Append(categories, theCurrentDescCategory + "\n" + theCurrentLine);
        } else {
            for (let A_Index9 = 0; A_Index9 < HTVM_Size(categories) + 0; A_Index9++) {
                if (Trim(StrLower(StrSplit(categories[A_Index9], "\n", 1))) == Trim(theCurrentDescCategory)) {
                    didWeFindSameCategory = 1;
                    categories[A_Index9] = categories[A_Index9] + "\n" + theCurrentLine;
                    break;
                }
            }
            if (didWeFindSameCategory == 0) {
                HTVM_Append(categories, theCurrentDescCategory + "\n" + theCurrentLine);
            }
        }
    }
    for (let A_Index10 = 0; A_Index10 < 20 + 0; A_Index10++) {
        //print("==========================")
    }
    var outMDup = "# HTVM Documentation\n\n1. [Introduction](#introduction-to-htvm)  \nUnderstand why HTVM is the future of programming.  \n\n2. [OSP (Objectively Simplified Programming) Paradigm](#osp-objectively-simplified-programming-paradigm)  \nLearn about the new paradigm that replaces traditional object-oriented programming.  \n\n3. [Built-in Functions](#built-in-functions)  \nExplore the wide range of built-in functions categorized for ease of use.  \n\n---\n\n## Introduction to HTVM\n\n[Go back](#htvm-documentation) \n\nHTVM is a revolutionary tool designed to replace traditional programming. With HTVM, you can create your own programming language directly [here](https://themaster1127.github.io/HTVM/).\n\nWhat makes HTVM powerful:  \n- **Syntax Customization**:  \n  Here’s what you can change:  \n  - **Keywords**: Modify the keywords used for " + Chr(96) + "if" + Chr(96) + " statements, " + Chr(96) + "while" + Chr(96) + " loops, " + Chr(96) + "for" + Chr(96) + " loops, and more.  \n  - **Operators**: Change the operators like " + Chr(96) + "==" + Chr(96) + ", " + Chr(96) + "!=" + Chr(96) + ", and others to suit your needs.  \n\n- **Inspiration from AutoHotKey**:  \n  Features like " + Chr(96) + "Loop" + Chr(96) + " and " + Chr(96) + "Loop, Parse" + Chr(96) + " (just like in AutoHotKey) are supported and customizable.  \n\n- **Cross-Language Compatibility**:  \n  Languages created with HTVM can be transpiled into **C++**, **Python**, and **JavaScript**.  \n\n- **Static Typing**:  \n  Types are required when converting to C++, but are optional for Python and JavaScript.  \n\n- **Built-in Functions**:  \n  Instead of libraries, HTVM offers built-in functions organized into categories. Scroll to the [Built-in Functions](#built-in-functions) section for more details.  \n\n## Core Features\n\n### Language Configuration\n- **Target Language Selection**\n  - Choose between **C++**, **Python** and **JavaScript** \n  - Specify file extensions for output files\n  - Configure HTML wrapping for JavaScript output\n\n### Syntax Customization\n- **Code Block Style**\n  - Toggle between curly braces " + Chr(96) + "{}" + Chr(96) + " or " + Chr(96) + "end" + Chr(96) + " keywords\n  - Enable/disable Python-style colon syntax\n  - Customize parentheses usage\n  - Control semicolon placement\n\n- **Function Definitions**\n  - Toggle function keywords\n  - Customize async main function for JavaScript\n  - Configure global variable handling\n\n### Type System\n- **Basic Types**\n  - Integer (INT)\n  - String (STR)\n  - Boolean (BOOL)\n  - Float (FLOAT)\n\n- **Extended Integer Types**\n  - INT8\n  - INT16\n  - INT32\n  - INT64\n\n### Control Structures\n- **Conditional Statements**\n  - If/Else/ElseIf\n  - Switch/Case/Default\n  - Custom keywords for all conditional operators\n\n- **Loops**\n  - While loops\n  - For loops with customizable syntax\n  - Infinite loops\n  - Parse loops (AutoHotkey-style)\n  - Custom indexing (0-based or 1-based)\n  - Loop control (break, continue)\n\n### Arrays and Collections\n- **Array Types**\n  - Integer arrays\n  - String arrays\n  - Float arrays\n  - Boolean arrays\n\n- **Array Operations**\n  - Append\n  - Pop\n  - Insert\n  - Remove\n  - Size\n  - IndexOf\n\n### Error Handling\n- **Exception Management**\n  - Try blocks\n  - Catch blocks\n  - Finally blocks\n  - Custom error messages\n  - Throw statements\n\n### JavaScript-Specific Features\n- **Variable Declaration**\n  - var, let, const keywords\n  - Automatic var declaration option\n  - await keyword support\n\n### Operators\n- **Assignment Operators**\n  - Basic assignment\n  - Addition assignment\n  - Subtraction assignment\n  - Multiplication assignment\n  - Division assignment\n  - Concatenation assignment\n\n- **Comparison Operators**\n  - Equal to\n  - Not equal to\n  - Greater than\n  - Less than\n  - Greater than or equal to\n  - Less than or equal to\n\n- **Logical Operators**\n  - AND\n  - OR\n  - NOT\n\n### Comments\n- Single-line comments\n- Multi-line comments\n- Custom comment symbols\n\n### AutoHotkey-Inspired Features\n- **Loop Variables**\n  - A_Index (customizable)\n  - A_LoopField (customizable)\n- **Loop Types**\n  - Parse loops\n  - Count loops\n  - Infinite loops\n\n## Configuration Options\n\n### Syntax Style\n- " + Chr(96) + "useFuncKeyWord" + Chr(96) + ": Toggle function definition keywords\n- " + Chr(96) + "useCurlyBraces" + Chr(96) + ": Toggle curly brace block definitions\n- " + Chr(96) + "useEnd" + Chr(96) + ": Toggle 'end' keyword for block closure\n- " + Chr(96) + "useSemicolon" + Chr(96) + ": Toggle statement-ending semicolons\n- " + Chr(96) + "useParentheses" + Chr(96) + ": Configure parentheses requirements\n- " + Chr(96) + "usePythonicColonSyntax" + Chr(96) + ": Enable Python-style block definitions\n\n### JavaScript Configuration\n- " + Chr(96) + "useInJavaScriptAlwaysUseVar" + Chr(96) + ": Force 'var' declarations\n- " + Chr(96) + "useJavaScriptInAfullHTMLfile" + Chr(96) + ": Enable HTML wrapping\n- " + Chr(96) + "useJavaScriptAmainFuncDef" + Chr(96) + ": Configure async main function\n\n### Loop Configuration\n- " + Chr(96) + "AHKlikeLoopsIndexedAt" + Chr(96) + ": Set loop index starting value\n- " + Chr(96) + "forLoopLang" + Chr(96) + ": Select loop syntax style\n- " + Chr(96) + "keyWordAIndex" + Chr(96) + ": Customize loop index variable name\n- " + Chr(96) + "keyWordALoopField" + Chr(96) + ": Customize loop field variable name\n\n\nHTVM empowers developers to create programming languages tailored to their needs while maintaining compatibility with modern technologies.  \n\n---\n\n## OSP (Objectively Simplified Programming) Paradigm  \n\n[Go back](#htvm-documentation) \n\nOSP (Objectively Simplified Programming) is a paradigm designed to replace OOP since OOP was a mistake. To learn OSP you need to first forget everything about OOP. Forget about concepts like inheritance, polymorphism, encapsulation, private/public keywords and instances.\n\nOSP eliminates the complexities of object-oriented programming.  \n\nHere’s how OSP works:  \n- **Hierarchies**:  \n  - **Alliance**: The top-level structure, defined using the " + Chr(96) + "alliance" + Chr(96) + " keyword. \n  - **Crew**: Sub-levels within an alliance, defined using the " + Chr(96) + "crew" + Chr(96) + " keyword.  \n  - **Method**: Functions defined within alliances or crews using the " + Chr(96) + "method" + Chr(96) + " keyword.  \n  - **Object**: Objects are defined using the " + Chr(96) + "def obj" + Chr(96) + " keyword.  \n\n- **Properties**:  \n  - Defined within objects using the " + Chr(96) + "porp" + Chr(96) + " keyword. You must specify the type, even when converting to Python or JavaScript, for readability.  \n\n\n### **The " + Chr(96) + "this" + Chr(96) + " Keyword**:\n\n- **Definition**:  \n  The " + Chr(96) + "this" + Chr(96) + " keyword is a reference to the current object that invoked a method. In OSP, " + Chr(96) + "this" + Chr(96) + " is **explicitly required to refer to objects**, and **you must always specify the full path** of objects and their properties when using it. Additionally, " + Chr(96) + "this" + Chr(96) + " is **only valid within methods**, as it represents the object calling that specific method.\n\n---\n\n### **Key Rules**:\n1. **Full Path Requirement**:  \n   - In OSP, **you must always specify the full path** of objects and properties when using " + Chr(96) + "this" + Chr(96) + ".  \n   - For example:  \n     - **Correct**: " + Chr(96) + "Movable.Vehicles.Car.fuel" + Chr(96) + "  \n     - **Incorrect**: " + Chr(96) + "fuel" + Chr(96) + "\n\n2. **Only Inside Methods**:  \n   - The " + Chr(96) + "this" + Chr(96) + " keyword can **only** be used inside a method. It refers to the object that invoked the method and provides context for operations on that object.  \n   - Using " + Chr(96) + "this" + Chr(96) + " outside of a method will result in an error, as there is no calling object to reference.\n\n---\n\n### **Explanation Using the Example**:\n" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "cpp\nmethod void move(this) {\n    if (this == " + Chr(34) + "Movable.Vehicles.Car" + Chr(34) + ") {\n        if (Movable.Vehicles.Car.fuel " + Chr(62) + " 0) {\n            print(" + Chr(34) + "The car is driving." + Chr(34) + ")\n            Movable.Vehicles.Car.fuel = Movable.Vehicles.Car.fuel - 10\n        } else {\n            print(" + Chr(34) + "The car is out of fuel." + Chr(34) + ")\n            Movable.Vehicles.Car.hasFUEL = false\n        }\n    }\n    else if (this == " + Chr(34) + "Movable.Vehicles.Bike" + Chr(34) + ") {\n        if (Movable.Vehicles.Bike.energy " + Chr(62) + " 0) {\n            print(" + Chr(34) + "The bike is pedaling." + Chr(34) + ")\n            Movable.Vehicles.Bike.energy = Movable.Vehicles.Bike.energy - 5\n        } else {\n            print(" + Chr(34) + "The bike is out of energy." + Chr(34) + ")\n            Movable.Vehicles.Bike.hasENERGY = false\n        }\n    }\n}\n" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "\n- The " + Chr(96) + "this" + Chr(96) + " keyword in this method represents the specific object calling " + Chr(96) + "move()" + Chr(96) + ".  \n  For instance:\n  - If " + Chr(96) + "this == " + Chr(34) + "Movable.Vehicles.Car" + Chr(34) + "" + Chr(96) + ", the method knows the caller is the **Car object**, and it manipulates " + Chr(96) + "Movable.Vehicles.Car" + Chr(96) + " properties.\n  - Similarly, if " + Chr(96) + "this == " + Chr(34) + "Movable.Vehicles.Bike" + Chr(34) + "" + Chr(96) + ", the method operates on the **Bike object**.\n\n- If you try to use " + Chr(96) + "this" + Chr(96) + " **outside of any method**, it won’t work because " + Chr(96) + "this" + Chr(96) + " has no object context to refer to.  \n  For example:\n  " + Chr(96) + "" + Chr(96) + "" + Chr(96) + " cpp\n  def obj Car {\n      prop int fuel = 100\n      print(this)  // This will cause an error!\n  }\n  " + Chr(96) + "" + Chr(96) + "" + Chr(96) + "\n\n---\n\n### **Why This Restriction Exists**:\n1. **Object Context**:  \n   - The " + Chr(96) + "this" + Chr(96) + " keyword needs a calling object to provide context. Without a method invocation, there’s no object to reference.\n\n2. **Scope Control**:  \n   - Limiting " + Chr(96) + "this" + Chr(96) + " to methods ensures clear and explicit usage, making code easier to understand and debug.\n\n3. **Example: Calling a Method with an Object**:  \n   - To use the " + Chr(96) + "this" + Chr(96) + " keyword, you must **pass an object** when invoking the method:  \n   " + Chr(96) + "" + Chr(96) + "" + Chr(96) + "cpp\n   allianceName.crewName.move(allianceName.crewName.objName)\n   " + Chr(96) + "" + Chr(96) + "" + Chr(96) + "\n   - Here:\n     - " + Chr(96) + "allianceName" + Chr(96) + " is the main alliance.\n     - " + Chr(96) + "crewName" + Chr(96) + " is the crew containing the method " + Chr(96) + "move" + Chr(96) + ".\n     - " + Chr(96) + "objName" + Chr(96) + " is the specific object being passed to the method. This allows " + Chr(96) + "this" + Chr(96) + " to refer to " + Chr(96) + "objName" + Chr(96) + " inside the method.\n\n---\n\n## **You Don’t Need an Alliance or Crew to Define Objects**\n- In OSP, you can define objects (" + Chr(96) + "def obj" + Chr(96) + ") directly without placing them inside an **alliance** or a **crew**.  \n- This makes it flexible to create standalone objects when you don’t need a larger structure.  \n\n### **Example: Standalone Object Definition**\n" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "cpp\ndef obj Standalone {\n    prop int value = 10\n    prop str name = " + Chr(34) + "Independent" + Chr(34) + "\n}\n" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "\n\nto access later just use:\n\n" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "cpp\nStandalone.value\nStandalone.name\n" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "\n\n---\n\n### **Methods in Alliances**\n- Methods can also be defined directly in an **alliance**, without being part of a **crew** and the opposite is well.\n\n### **Example: Method in an Alliance**\n" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "cpp\nalliance ExampleAlliance {\n    method void greet() {\n        print(" + Chr(34) + "Hello from ExampleAlliance!" + Chr(34) + ")\n    }\n}\n" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "\n\nto call greet just do:\n\n" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "cpp\nExampleAlliance.greet()\n" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "\n\n## Global Accessibility:  \n  - There are no scopes in OSP. As long as a variable or structure is defined above, it is accessible below. Everything is global, and the full path must always be used.  \n\n## Arrays:  \n  - When using arrays you need to create a temporary array and then copy it to another like this:\n\n" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "py\ndef obj name {\n    arr str temp\n    prop arr str prop1 = temp\n    prop arr str prop2 = temp\n    prop arr str prop3 = temp\n    prop arr str prop4 = temp\n}\n" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "\n\n### **Summary**:\n- **Full Paths Always**: Explicit references, such as " + Chr(96) + "Movable.Vehicles.Car.fuel" + Chr(96) + ", are mandatory in OSP. Always use the full path to reference objects. This avoids ambiguity and ensures that each object is uniquely identified within the code.\n- **Only Inside Methods**: The " + Chr(96) + "this" + Chr(96) + " keyword can only be used inside a method to refer to the calling object. It is not valid outside of a method because it requires the context of the method invocation to work correctly.\n- **Promotes Clarity**: These rules ensure consistency, clarity, and unambiguous functionality in OSP. By restricting the use of " + Chr(96) + "this" + Chr(96) + " to methods and requiring full paths, the code remains explicit and easier to follow.\n- **Helps with Debugging**: Since " + Chr(96) + "this" + Chr(96) + " is only valid inside methods, errors related to improper use are easier to detect. Using full paths also helps pinpoint issues more precisely by avoiding confusion with similarly named objects.\n- **Encourages Best Practices**: These guidelines encourage a more structured and organized approach to coding in OSP, fostering a clearer and more maintainable codebase in larger projects.\n\n---\n\n## Note:\n\n### Never use underscores when naming things in OSP. Otherwise, you can use them, but be cautious because underscores can be unstable.\n\n\n#### Example of OSP\n\n" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "cpp\nalliance Movable {\n    crew Vehicles {\n        def obj Car {\n            prop int door = 4\n            prop int fuel = 100\n            prop bool hasFUEL = true\n        }\n        def obj Bike {\n            prop bool hasGears = true\n            prop int energy = 100\n            prop bool hasENERGY = true\n        }\n\n        method void move(this) {\n            if (this == " + Chr(34) + "Movable.Vehicles.Car" + Chr(34) + ") {\n                if (Movable.Vehicles.Car.fuel " + Chr(62) + " 0) {\n                    print(" + Chr(34) + "The car is driving." + Chr(34) + ")\n                    Movable.Vehicles.Car.fuel = Movable.Vehicles.Car.fuel - 10\n                } else {\n                    print(" + Chr(34) + "The car is out of fuel." + Chr(34) + ")\n                    Movable.Vehicles.Car.hasFUEL = false\n                }\n            }\n            else if (this == " + Chr(34) + "Movable.Vehicles.Bike" + Chr(34) + ") {\n                if (Movable.Vehicles.Bike.energy " + Chr(62) + " 0) {\n                    print(" + Chr(34) + "The bike is pedaling." + Chr(34) + ")\n                    Movable.Vehicles.Bike.energy = Movable.Vehicles.Bike.energy - 5\n                } else {\n                    print(" + Chr(34) + "The bike is out of energy." + Chr(34) + ")\n                    Movable.Vehicles.Bike.hasENERGY = false\n                }\n            }\n        }\n    }\n    \n    crew settings {\n        def obj GeneralSettings {\n            prop str difficulty = " + Chr(34) + "normal" + Chr(34) + "\n            prop int volume = 50\n            prop str resolution = " + Chr(34) + "1920x1080" + Chr(34) + "\n        }\n        def obj AudioSettings {\n            prop int masterVolume = 70\n            prop int musicVolume = 50\n            prop int sfxVolume = 40\n        }\n        def obj DisplaySettings {\n            prop bool fullscreen = true\n            prop str aspectRatio = " + Chr(34) + "16:9" + Chr(34) + "\n        }\n    }\n    \n    crew actions {\n        // General Settings Methods\n        method void resetGeneralSettings() {\n            Movable.settings.GeneralSettings.difficulty = STR(" + Chr(34) + "normal" + Chr(34) + ")\n            Movable.settings.GeneralSettings.volume = 50\n            Movable.settings.GeneralSettings.resolution = STR(" + Chr(34) + "1920x1080" + Chr(34) + ")\n            print(" + Chr(34) + "General settings reset to default." + Chr(34) + ")\n        }\n        method void printGeneralSettings() {\n            print(" + Chr(34) + "General Settings:" + Chr(34) + ")\n            print(" + Chr(34) + "Difficulty: " + Chr(34) + " + Movable.settings.GeneralSettings.difficulty)\n            print(" + Chr(34) + "Volume: " + Chr(34) + " + STR(Movable.settings.GeneralSettings.volume))\n            print(" + Chr(34) + "Resolution: " + Chr(34) + " + Movable.settings.GeneralSettings.resolution)\n        }\n\n        // Audio Settings Methods\n        method void resetAudioSettings() {\n            Movable.settings.AudioSettings.masterVolume = 70\n            Movable.settings.AudioSettings.musicVolume = 50\n            Movable.settings.AudioSettings.sfxVolume = 40\n            print(" + Chr(34) + "Audio settings reset to default." + Chr(34) + ")\n        }\n        method void printAudioSettings() {\n            print(" + Chr(34) + "Audio Settings:" + Chr(34) + ")\n            print(" + Chr(34) + "Master Volume: " + Chr(34) + " + STR(Movable.settings.AudioSettings.masterVolume))\n            print(" + Chr(34) + "Music Volume: " + Chr(34) + " + STR(Movable.settings.AudioSettings.musicVolume))\n            print(" + Chr(34) + "SFX Volume: " + Chr(34) + " + STR(Movable.settings.AudioSettings.sfxVolume))\n        }\n\n        // Display Settings Methods\n        method void resetDisplaySettings() {\n            Movable.settings.DisplaySettings.fullscreen = true\n            Movable.settings.DisplaySettings.aspectRatio = STR(" + Chr(34) + "16:9" + Chr(34) + ")\n            print(" + Chr(34) + "Display settings reset to default." + Chr(34) + ")\n        }\n        method void printDisplaySettings() {\n            print(" + Chr(34) + "Display Settings:" + Chr(34) + ")\n            print(" + Chr(34) + "Fullscreen: " + Chr(34) + " + STR(Movable.settings.DisplaySettings.fullscreen))\n            print(" + Chr(34) + "Aspect Ratio: " + Chr(34) + " + Movable.settings.DisplaySettings.aspectRatio)\n        }\n    }\n\n    crew array {\n        def obj name {\n            arr str temp\n            prop arr str prop1 = temp\n            prop arr str prop2 = temp\n            prop arr str prop3 = temp\n            prop arr str prop4 = temp\n        }\n    }\n    \n}\n\nmain\n// Test vehicle movement\nwhile (Movable.Vehicles.Car.hasFUEL == true) && (Movable.Vehicles.Bike.hasENERGY = true) {\n    Movable.Vehicles.move(Movable.Vehicles.Car)\n    Movable.Vehicles.move(Movable.Vehicles.Bike)\n    print(" + Chr(34) + "=====================================" + Chr(34) + ")\n}\n\n// Test settings manipulation\nMovable.settings.GeneralSettings.difficulty = STR(" + Chr(34) + "hard" + Chr(34) + ")\nMovable.settings.GeneralSettings.volume = 80\nMovable.settings.GeneralSettings.resolution = STR(" + Chr(34) + "2560x1440" + Chr(34) + ")\nMovable.settings.AudioSettings.masterVolume = 90\nMovable.settings.AudioSettings.musicVolume = 60\nMovable.settings.AudioSettings.sfxVolume = 50\nMovable.settings.DisplaySettings.fullscreen = false\nMovable.settings.DisplaySettings.aspectRatio = STR(" + Chr(34) + "21:9" + Chr(34) + ")\n\nMovable.actions.printGeneralSettings()\nMovable.actions.printAudioSettings()\nMovable.actions.printDisplaySettings()\n\nMovable.actions.resetGeneralSettings()\nMovable.actions.resetAudioSettings()\nMovable.actions.resetDisplaySettings()\n\nMovable.actions.printGeneralSettings()\nMovable.actions.printAudioSettings()\nMovable.actions.printDisplaySettings()\n\n// Test array manipulation\nMovable.array.name.prop1.push(" + Chr(34) + "1text1" + Chr(34) + ")\nMovable.array.name.prop1.push(" + Chr(34) + "1text2" + Chr(34) + ")\nMovable.array.name.prop1.push(" + Chr(34) + "1text3" + Chr(34) + ")\nMovable.array.name.prop2.push(" + Chr(34) + "2text1" + Chr(34) + ")\nMovable.array.name.prop2.push(" + Chr(34) + "2text2" + Chr(34) + ")\nMovable.array.name.prop2.push(" + Chr(34) + "2text3" + Chr(34) + ")\nMovable.array.name.prop3.push(" + Chr(34) + "3text1" + Chr(34) + ")\nMovable.array.name.prop3.push(" + Chr(34) + "3text2" + Chr(34) + ")\nMovable.array.name.prop3.push(" + Chr(34) + "3text3" + Chr(34) + ")\nMovable.array.name.prop4.push(" + Chr(34) + "4text1" + Chr(34) + ")\nMovable.array.name.prop4.push(" + Chr(34) + "4text2" + Chr(34) + ")\nMovable.array.name.prop4.push(" + Chr(34) + "4text3" + Chr(34) + ")\n\n// why this\n// cuz python used len(param) insed of param.len() so it meses up evrything\n// if using OSP objects that have a dot (.) it doset work in python to get the lenght\n// but for a name whit no dots it works\n\narr str arrayTempOnlyGetSize1 = Movable.array.name.prop1\narr str arrayTempOnlyGetSize2 = Movable.array.name.prop2\narr str arrayTempOnlyGetSize3 = Movable.array.name.prop3\narr str arrayTempOnlyGetSize4 = Movable.array.name.prop4\n\n\n\n\nLoop, % arrayTempOnlyGetSize1.size() \n{\nprint(Movable.array.name.prop1[A_Index])\n}\nLoop, % arrayTempOnlyGetSize2.size() {\n    print(Movable.array.name.prop2[A_Index])\n}\nLoop, % arrayTempOnlyGetSize3.size() {\n    print(Movable.array.name.prop3[A_Index])\n}\nLoop, % arrayTempOnlyGetSize4.size() {\n    print(Movable.array.name.prop4[A_Index])\n}\n\n" + Chr(96) + "" + Chr(96) + "" + Chr(96) + "\n\nOSP simplifies programming while ensuring compatibility with **C++**, **Python**, and **JavaScript**.  \n\n---\n\n## Built-in Functions  \n\n[Go back](#htvm-documentation) \n\nHTVM includes a variety of built-in functions organized into categories for convenience.\n\n";
    var outMD = "";
    var str1 = "";
    var str2 = "";
    var str3 = "";
    var str4 = "";
    var str5 = "";
    var str6 = "";
    var str7 = "";
    var str8 = "";
    var str9 = "";
    var str10 = "";
    var str11 = "";
    var str12 = "";
    var str13 = "";
    var str14 = "";
    var str15 = "";
    var str16 = "";
    var str17 = "";
    var str18 = "";
    var str19 = "";
    var str20 = "";
    var str21 = "";
    var str22 = "";
    var str23 = "";
    var str24 = "";
    var str25 = "";
    var str26 = "";
    var str27 = "";
    for (let A_Index11 = 0; A_Index11 < HTVM_Size(categories) + 0; A_Index11++) {
        //print(categories[A_Index11])
        str1 = Trim(StrTitleCase(Trim(StrSplit(categories[A_Index11], "\n", 1)))) + " Functions";
        // 1. [String Functions](#string-functions)
        str2 = STR(A_Index11 + 1) + ". [" + str1 + "](#" + Trim(StrReplace(StrLower(str1), " ", "-")) + ")";
        outMD += str2 + "\n";
        // [Go back](#built-in-functions)
    }
    outMD += "\n---\n\n";
    var categoriesElement = "";
    for (let A_Index12 = 0; A_Index12 < HTVM_Size(categories) + 0; A_Index12++) {
        //print(categories[A_Index12])
        str1 = Trim(StrTitleCase(Trim(StrSplit(categories[A_Index12], "\n", 1)))) + " Functions";
        // ## String Functions
        str2 = "## " + Trim(str1) + "\n\n[Go back](#built-in-functions)\n\n";
        str10 = "[Go back](#" + Trim(StrReplace(StrLower(str1), " ", "-")) + ")";
        outMD += str2;
        // 1. [str1](#str1)
        // 2. [str2](#str2)
        // 3. [str3](#str3)
        categoriesElement = categories[A_Index12];
        items13 = LoopParseFunc(categoriesElement, "\n", "\r")
        for (let A_Index13 = 0; A_Index13 < items13.length + 0; A_Index13++) {
            const A_LoopField13 = items13[A_Index13 - 0];
            if (A_Index13 != 0) {
                if (Trim(A_LoopField13) != "") {
                    str1 = Trim(StrSplit(StrSplit(A_LoopField13, "|", 1), ":", 2));
                    str3 = STR(A_Index13) + ". [" + str1 + "](#" + Trim(StrReplace(StrLower(str1), " ", "-")) + ")";
                    outMD += str3 + "\n";
                }
            }
        }
        outMD += "\n---\n\n**HTVM built-in functions are designed to work across C++, Python, and JavaScript, with availability varying depending on language-specific capabilities, libraries, and syntax. Some functions are supported in JavaScript but not in Python or C++, while others are available in all or some languages.**\n\n**HTVM build-in functions availability.**\n\n| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |\n|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|\n";
        items14 = LoopParseFunc(categoriesElement, "\n", "\r")
        for (let A_Index14 = 0; A_Index14 < items14.length + 0; A_Index14++) {
            const A_LoopField14 = items14[A_Index14 - 0];
            if (A_Index14 != 0) {
                if (Trim(A_LoopField14) != "") {
                    str1 = Trim(StrSplit(StrSplit(A_LoopField14, "|", 1), ":", 2));
                    // cpp py js and more
                    str4 = Trim(StrSplit(A_LoopField14, "|", 3));
                    str5 = Trim(StrSplit(A_LoopField14, "|", 4));
                    str6 = Trim(StrSplit(A_LoopField14, "|", 5));
                    str7 = Trim(StrSplit(A_LoopField14, "|", 6));
                    //
                    str11 = Trim(StrSplit(A_LoopField14, "|", 7));
                    str12 = Trim(StrSplit(A_LoopField14, "|", 8));
                    str13 = Trim(StrSplit(A_LoopField14, "|", 9));
                    str14 = Trim(StrSplit(A_LoopField14, "|", 10));
                    str15 = Trim(StrSplit(A_LoopField14, "|", 11));
                    str16 = Trim(StrSplit(A_LoopField14, "|", 12));
                    str17 = Trim(StrSplit(A_LoopField14, "|", 13));
                    str18 = Trim(StrSplit(A_LoopField14, "|", 14));
                    str19 = Trim(StrSplit(A_LoopField14, "|", 15));
                    str20 = Trim(StrSplit(A_LoopField14, "|", 16));
                    str21 = Trim(StrSplit(A_LoopField14, "|", 17));
                    // | str1 | Yes | No | Yes | and more
                    str3 = "| " + str1 + " | " + str4 + " | " + str5 + " | " + str6 + " | " + str7 + " |" + str11 + " |" + str12 + " |" + str13 + " |" + str14 + " |" + str15 + " |" + str16 + " |" + str17 + " |" + str18 + " |" + str19 + " |" + str20 + " |" + str21 + " |";
                    outMD += str3 + "\n";
                }
            }
        }
        outMD += "\n---\n\n";
        items15 = LoopParseFunc(categoriesElement, "\n", "\r")
        for (let A_Index15 = 0; A_Index15 < items15.length + 0; A_Index15++) {
            const A_LoopField15 = items15[A_Index15 - 0];
            if (A_Index15 != 0) {
                if (Trim(A_LoopField15) != "") {
                    str1 = Trim(StrSplit(StrSplit(A_LoopField15, "|", 1), ":", 2));
                    str2 = "### " + str1 + "\n\n" + Trim(str10) + "\n\n**HTVM build-in functions availability.**\n\n| Functions | C++   | Python | JavaScript | Go   | Lua   | C#   | Java   | Kotlin | Ruby  | Nim   | AutoHotKey | Swift | Dart  | TypeScript | Groovy |\n|-----------|-------|--------|------------|------|-------|------|--------|--------|-------|-------|------------|-------|-------|------------|--------|\n";
                    // cpp py js
                    str4 = Trim(StrSplit(A_LoopField15, "|", 3));
                    str5 = Trim(StrSplit(A_LoopField15, "|", 4));
                    str6 = Trim(StrSplit(A_LoopField15, "|", 5));
                    str7 = Trim(StrSplit(A_LoopField15, "|", 6));
                    //
                    str11 = Trim(StrSplit(A_LoopField15, "|", 7));
                    str12 = Trim(StrSplit(A_LoopField15, "|", 8));
                    str13 = Trim(StrSplit(A_LoopField15, "|", 9));
                    str14 = Trim(StrSplit(A_LoopField15, "|", 10));
                    str15 = Trim(StrSplit(A_LoopField15, "|", 11));
                    str16 = Trim(StrSplit(A_LoopField15, "|", 12));
                    str17 = Trim(StrSplit(A_LoopField15, "|", 13));
                    str18 = Trim(StrSplit(A_LoopField15, "|", 14));
                    str19 = Trim(StrSplit(A_LoopField15, "|", 15));
                    str20 = Trim(StrSplit(A_LoopField15, "|", 16));
                    str21 = Trim(StrSplit(A_LoopField15, "|", 17));
                    // | str1 | Yes | No | Yes | and more
                    str3 = "| " + str1 + " | " + str4 + " | " + str5 + " | " + str6 + " | " + str7 + " |" + str11 + " |" + str12 + " |" + str13 + " |" + str14 + " |" + str15 + " |" + str16 + " |" + str17 + " |" + str18 + " |" + str19 + " |" + str20 + " |" + str21 + " |";
                    str8 = "";
                    str9 = Trim(StrSplit(StrSplit(A_LoopField15, "|", 2), "description:", 2));
                    items16 = LoopParseFunc(str9, "~~~")
                    for (let A_Index16 = 0; A_Index16 < items16.length + 0; A_Index16++) {
                        const A_LoopField16 = items16[A_Index16 - 0];
                        if (A_Index16 != 0) {
                            if (A_LoopField16 != "") {
                                str7 += A_LoopField16 + "\n";
                            }
                        }
                    }
                    outMD += str2 + str3 + "\n\n" + str8 + "\n---\n\n";
                }
            }
        }
    }
    var htmlUP = "" + Chr(60) + "!DOCTYPE html" + Chr(62) + "\n" + Chr(60) + "html lang=" + Chr(34) + "en" + Chr(34) + "" + Chr(62) + "\n" + Chr(60) + "head" + Chr(62) + "\n    " + Chr(60) + "meta charset=" + Chr(34) + "UTF-8" + Chr(34) + "" + Chr(62) + "\n    " + Chr(60) + "meta name=" + Chr(34) + "viewport" + Chr(34) + " content=" + Chr(34) + "width=device-width, initial-scale=1.0" + Chr(34) + "" + Chr(62) + "\n    " + Chr(60) + "title" + Chr(62) + "GitHub-Style Markdown with Ace Editor" + Chr(60) + "/title" + Chr(62) + "\n\n    " + Chr(60) + "!-- Link to markdown-it library --" + Chr(62) + "\n    " + Chr(60) + "script src=" + Chr(34) + "https://cdn.jsdelivr.net/npm/markdown-it@12.0.4/dist/markdown-it.min.js" + Chr(34) + "" + Chr(62) + "" + Chr(60) + "/script" + Chr(62) + "\n    \n    " + Chr(60) + "!-- Ace Editor --" + Chr(62) + "\n    " + Chr(60) + "script src=" + Chr(34) + "https://cdnjs.cloudflare.com/ajax/libs/ace/1.9.6/ace.js" + Chr(34) + "" + Chr(62) + "" + Chr(60) + "/script" + Chr(62) + "\n    " + Chr(60) + "script src=" + Chr(34) + "https://cdnjs.cloudflare.com/ajax/libs/ace/1.9.6/theme-monokai.min.js" + Chr(34) + "" + Chr(62) + "" + Chr(60) + "/script" + Chr(62) + "\n    " + Chr(60) + "script src=" + Chr(34) + "https://cdnjs.cloudflare.com/ajax/libs/ace/1.9.6/mode-javascript.min.js" + Chr(34) + "" + Chr(62) + "" + Chr(60) + "/script" + Chr(62) + "\n    " + Chr(60) + "script src=" + Chr(34) + "https://cdnjs.cloudflare.com/ajax/libs/ace/1.9.6/mode-python.min.js" + Chr(34) + "" + Chr(62) + "" + Chr(60) + "/script" + Chr(62) + "\n    " + Chr(60) + "script src=" + Chr(34) + "https://cdnjs.cloudflare.com/ajax/libs/ace/1.9.6/mode-html.min.js" + Chr(34) + "" + Chr(62) + "" + Chr(60) + "/script" + Chr(62) + "\n    " + Chr(60) + "script src=" + Chr(34) + "https://cdnjs.cloudflare.com/ajax/libs/ace/1.9.6/mode-css.min.js" + Chr(34) + "" + Chr(62) + "" + Chr(60) + "/script" + Chr(62) + "\n    " + Chr(60) + "script src=" + Chr(34) + "https://cdnjs.cloudflare.com/ajax/libs/ace/1.9.6/mode-json.min.js" + Chr(34) + "" + Chr(62) + "" + Chr(60) + "/script" + Chr(62) + "\n\n    " + Chr(60) + "!-- Font Awesome for icons --" + Chr(62) + "\n    " + Chr(60) + "link rel=" + Chr(34) + "stylesheet" + Chr(34) + " href=" + Chr(34) + "https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.15.4/css/all.min.css" + Chr(34) + "" + Chr(62) + "\n\n    " + Chr(60) + "style" + Chr(62) + "\n        /* Dark Mode Styles */\n        body {\n            background-color: #121212;\n            color: #e0e0e0;\n            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;\n            line-height: 1.6;\n            padding-left: 30px;\n            padding-right: 30px;\n            margin: 0;\n            word-wrap: break-word;\n        }\n\n        h1, h2, h3, h4, h5, h6 {\n            color: #ffffff;\n            position: relative;\n        }\n\n        /* Container for the markdown content */\n        #markdown-output {\n            background-color: #1e1e1e;\n            border-radius: 8px;\n            padding: 30px;\n            margin-top: 20px;\n            box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);\n        }\n\n        /* Header Styling */\n        h1 {\n            font-size: 2.5em;\n            border-bottom: 2px solid #444;\n            padding-bottom: 10px;\n        }\n\n        h2 {\n            color: #ffffff;\n            border-bottom: 1px solid #444;\n            padding-bottom: 5px;\n            margin-top: 30px;\n        }\n\n        h3 {\n            color: #81a1c1;\n            margin-top: 20px;\n        }\n\n        /* Links */\n        a {\n            color: #1e90ff;\n            text-decoration: none;\n        }\n\n        a:hover {\n            text-decoration: underline;\n        }\n\n        /* External link icon */\n        a.external-link:after {\n            content: " + Chr(34) + " " + Chr(92) + "2197" + Chr(34) + ";\n            display: inline-block;\n            margin-left: 4px;\n            font-size: 0.8em;\n        }\n        \n        /* Header anchor links that show on hover */\n        .header-anchor {\n            opacity: 0;\n            font-size: 0.8em;\n            margin-left: 8px;\n            color: #666;\n            transition: opacity 0.2s ease-in-out;\n        }\n        \n        h1:hover .header-anchor,\n        h2:hover .header-anchor,\n        h3:hover .header-anchor,\n        h4:hover .header-anchor,\n        h5:hover .header-anchor,\n        h6:hover .header-anchor {\n            opacity: 1;\n            color: #1e90ff;\n        }\n\n        /* Ace Editor Styling */\n        .ace-editor-container {\n            margin: 20px 0;\n            border-radius: 8px;\n            overflow: hidden;\n        }\n        \n        .ace-editor {\n            width: 100%;\n            border-radius: 8px;\n            /* Height will be set dynamically based on content */\n        }\n        \n        .ace-editor-header {\n            background-color: #333;\n            color: #fff;\n            padding: 8px 15px;\n            font-family: monospace;\n            font-size: 0.9em;\n            display: flex;\n            justify-content: space-between;\n            align-items: center;\n            border-top-left-radius: 8px;\n            border-top-right-radius: 8px;\n        }\n        \n        .ace-editor-language {\n            font-weight: bold;\n            color: #82aaff;\n        }\n\n        /* Copy Button Styling */\n        .copy-button {\n            background-color: #2a2a2a;\n            border: none;\n            color: #ccc;\n            border-radius: 4px;\n            padding: 3px 8px;\n            font-size: 12px;\n            cursor: pointer;\n            margin-right: 10px;\n            transition: all 0.2s ease;\n            display: flex;\n            align-items: center;\n        }\n        \n        .copy-button:hover {\n            background-color: #3a3a3a;\n            color: #fff;\n        }\n        \n        .copy-button i {\n            margin-right: 4px;\n        }\n        \n        .copy-success {\n            background-color: #28a745 !important;\n            color: white !important;\n        }\n\n        /* Inline code */\n        p code, li code {\n            background-color: #2b2b2b;\n            padding: 2px 5px;\n            border-radius: 3px;\n            font-family: Consolas, 'Courier New', monospace;\n        }\n\n        /* Table Styling */\n        table {\n            width: 100%;\n            margin: 20px 0;\n            border-collapse: collapse;\n        }\n\n        th, td {\n            padding: 10px;\n            text-align: left;\n            border: 1px solid #444;\n        }\n\n        th {\n            background-color: #333;\n        }\n\n        tr:nth-child(even) {\n            background-color: #2a2a2a;\n        }\n\n        tr:hover {\n            background-color: #444;\n        }\n        \n        /* Fix for internal links */\n        :target {\n            scroll-margin-top: 20px;\n            animation: highlight 2s ease;\n        }\n        \n        @keyframes highlight {\n            from { background-color: #333333; }\n            to { background-color: transparent; }\n        }\n    " + Chr(60) + "/style" + Chr(62) + "\n" + Chr(60) + "/head" + Chr(62) + "\n" + Chr(60) + "body" + Chr(62) + "\n\n    " + Chr(60) + "!-- Markdown content written in normal syntax --" + Chr(62) + "\n" + Chr(60) + "div id=" + Chr(34) + "markdown-content" + Chr(34) + " style=" + Chr(34) + "display:none;" + Chr(34) + "" + Chr(62) + "\n\n\n\n";
    var htmlDOWN = "\n\n" + Chr(60) + "/div" + Chr(62) + "\n\n    " + Chr(60) + "br" + Chr(62) + "" + Chr(60) + "br" + Chr(62) + "\n\n    " + Chr(60) + "!-- A div to display the rendered HTML --" + Chr(62) + "\n    " + Chr(60) + "div id=" + Chr(34) + "markdown-output" + Chr(34) + "" + Chr(62) + "" + Chr(60) + "/div" + Chr(62) + "\n\n    " + Chr(60) + "script" + Chr(62) + "\n        // Initialize Markdown-it with HTML enabled and proper heading IDs\n        var md = window.markdownit({\n            html: true,\n            linkify: true,\n            typographer: true\n        });\n        \n// Custom renderer for code blocks to use Ace Editor\n\n// Custom renderer for code blocks to use Ace Editor\n\nvar defaultCodeRenderer = md.renderer.rules.fence;\nmd.renderer.rules.fence = function(tokens, idx, options, env, self) {\n    var token = tokens[idx];\n    var language = token.info.trim() || 'text';\n    var code = token.content;\n    \n    // Generate a unique ID for the editor\n    var editorId = 'ace-editor-' + idx;\n    var codeId = 'code-content-' + idx;\n    var buttonId = 'copy-button-' + idx;\n    \n    // Create container for the ace editor\n    var html = '" + Chr(60) + "div class=" + Chr(34) + "ace-editor-container" + Chr(34) + "" + Chr(62) + "" + Chr(92) + "n';\n    html += '" + Chr(60) + "div class=" + Chr(34) + "ace-editor-header" + Chr(34) + "" + Chr(62) + "';\n    \n    // Add copy button before language\n    html += '" + Chr(60) + "div style=" + Chr(34) + "display: flex; align-items: center;" + Chr(34) + "" + Chr(62) + "';\n    html += '" + Chr(60) + "button id=" + Chr(34) + "' + buttonId + '" + Chr(34) + " class=" + Chr(34) + "copy-button" + Chr(34) + " data-code-id=" + Chr(34) + "' + codeId + '" + Chr(34) + "" + Chr(62) + "';\n    html += '" + Chr(60) + "i class=" + Chr(34) + "fas fa-copy" + Chr(34) + "" + Chr(62) + "" + Chr(60) + "/i" + Chr(62) + " Copy" + Chr(60) + "/button" + Chr(62) + "';\n    html += '" + Chr(60) + "span class=" + Chr(34) + "ace-editor-language" + Chr(34) + "" + Chr(62) + "' + language + '" + Chr(60) + "/span" + Chr(62) + "';\n    html += '" + Chr(60) + "/div" + Chr(62) + "';\n    \n    html += '" + Chr(60) + "span" + Chr(62) + "" + Chr(60) + "i class=" + Chr(34) + "fas fa-code" + Chr(34) + "" + Chr(62) + "" + Chr(60) + "/i" + Chr(62) + "" + Chr(60) + "/span" + Chr(62) + "" + Chr(60) + "/div" + Chr(62) + "" + Chr(92) + "n';\n    \n    // Create a pre element to hold the code initially\n    html += '" + Chr(60) + "pre id=" + Chr(34) + "' + editorId + '" + Chr(34) + " class=" + Chr(34) + "ace-editor" + Chr(34) + "" + Chr(62) + "' + escapeHtml(code) + '" + Chr(60) + "/pre" + Chr(62) + "" + Chr(92) + "n';\n    html += '" + Chr(60) + "div id=" + Chr(34) + "' + codeId + '" + Chr(34) + " style=" + Chr(34) + "display: none;" + Chr(34) + "" + Chr(62) + "' + escapeHtml(code) + '" + Chr(60) + "/div" + Chr(62) + "" + Chr(92) + "n';\n    html += '" + Chr(60) + "/div" + Chr(62) + "" + Chr(92) + "n';\n    \n    // Store the code and language for later use with Ace\n    setTimeout(function() {\n        initAceEditor(editorId, code, language);\n    }, 100);\n    \n    return html;\n};\n        \n// Function to initialize the Ace editor\nfunction initAceEditor(editorId, code, language) {\n    var editor = ace.edit(editorId);\n    editor.setTheme(" + Chr(34) + "ace/theme/monokai" + Chr(34) + ");\n    \n    // Map markdown language names to Ace mode names\n    var modeMap = {\n        'javascript': 'javascript',\n        'js': 'javascript',\n        'html': 'html',\n        'css': 'css',\n        'python': 'python',\n        'py': 'python',\n        'json': 'json'\n        // Add more mappings as needed\n    };\n    \n    // Set the correct mode based on language\n    var mode = modeMap[language.toLowerCase()] || 'text';\n    editor.session.setMode(" + Chr(34) + "ace/mode/" + Chr(34) + " + mode);\n    \n    // Set full code content directly to maintain formatting\n    editor.setValue(code);\n    editor.clearSelection();\n    \n    // Make editor read-only\n    editor.setReadOnly(true);\n    \n    // Disable wrap mode to preserve formatting\n    editor.getSession().setUseWrapMode(false);\n    \n    // Additional editor settings\n    editor.setShowPrintMargin(false);\n    editor.setHighlightActiveLine(true);\n    editor.setOptions({\n        fontSize: " + Chr(34) + "14px" + Chr(34) + ",\n        tabSize: 4,\n        useSoftTabs: true,\n        enableBasicAutocompletion: false,\n        enableSnippets: false,\n        enableLiveAutocompletion: false\n    });\n    \n    // Calculate the exact number of lines\n    var lineCount = editor.session.getLength();\n    \n    // Get the actual line height from the renderer\n    var lineHeight = editor.renderer.lineHeight;\n    \n    // Calculate exact height with a tiny buffer\n    var exactHeight = (lineCount * lineHeight);\n    \n    // Set the editor height to exactly fit the content\n    document.getElementById(editorId).style.height = exactHeight + " + Chr(34) + "px" + Chr(34) + ";\n    \n    // Final resize to update the editor view\n    editor.resize();\n}\n\n// Helper function to escape HTML\nfunction escapeHtml(unsafe) {\n    return unsafe\n        .replace(/&/g, " + Chr(34) + "&amp;" + Chr(34) + ")\n        .replace(/" + Chr(60) + "/g, " + Chr(34) + "&lt;" + Chr(34) + ")\n        .replace(/" + Chr(62) + "/g, " + Chr(34) + "&gt;" + Chr(34) + ")\n        .replace(/" + Chr(34) + "/g, " + Chr(34) + "&quot;" + Chr(34) + ")\n        .replace(/'/g, " + Chr(34) + "&#039;" + Chr(34) + ");\n}\n\n        \n        // Get the markdown content (from the hidden div)\n        var markdownText = document.getElementById(" + Chr(34) + "markdown-content" + Chr(34) + ").innerText;\n\n        // Convert markdown to HTML\n        var htmlContent = md.render(markdownText);\n\n        // Output the rendered HTML to the markdown-output div\n        document.getElementById(" + Chr(34) + "markdown-output" + Chr(34) + ").innerHTML = htmlContent;\n        \n        // Process all headings to add anchor links\n        document.querySelectorAll('#markdown-output h1, #markdown-output h2, #markdown-output h3, #markdown-output h4, #markdown-output h5, #markdown-output h6').forEach(function(heading) {\n            // Generate ID if none exists\n            if (!heading.id) {\n                heading.id = heading.textContent.toLowerCase().replace(/" + Chr(92) + "s+/g, '-').replace(/[^" + Chr(92) + "w-]/g, '');\n            }\n            \n            // Create an anchor element\n            var anchor = document.createElement('a');\n            anchor.className = 'header-anchor';\n            anchor.href = '#' + heading.id;\n            anchor.innerHTML = '" + Chr(60) + "i class=" + Chr(34) + "fas fa-link" + Chr(34) + "" + Chr(62) + "" + Chr(60) + "/i" + Chr(62) + "';\n            \n            // Add click event to update URL without refreshing page\n            anchor.addEventListener('click', function(e) {\n                e.preventDefault();\n                history.pushState(null, null, this.getAttribute('href'));\n                // Scroll to the element\n                document.getElementById(heading.id).scrollIntoView({\n                    behavior: 'smooth'\n                });\n            });\n            \n            // Add the anchor to the heading\n            heading.appendChild(anchor);\n        });\n        \n        // Process all links in the rendered markdown\n        document.querySelectorAll('#markdown-output a:not(.header-anchor)').forEach(function(link) {\n            // Check if it's an internal anchor link\n            if (link.getAttribute('href').startsWith('#')) {\n                // Add click event to update URL without refreshing page\n                link.addEventListener('click', function(e) {\n                    e.preventDefault();\n                    var targetId = this.getAttribute('href').substring(1);\n                    history.pushState(null, null, this.getAttribute('href'));\n                    // Scroll to the element\n                    document.getElementById(targetId).scrollIntoView({\n                        behavior: 'smooth'\n                    });\n                });\n            } else {\n                // It's an external link\n                link.setAttribute('target', '_blank');\n                link.setAttribute('rel', 'noopener noreferrer');\n                link.classList.add('external-link');\n            }\n        });\n        \n        // Set up clipboard functionality for copy buttons after DOM is fully loaded\n        document.addEventListener('DOMContentLoaded', function() {\n            setupCopyButtons();\n        });\n        \n        // Also set up copy buttons after the markdown is rendered\n        setTimeout(function() {\n            setupCopyButtons();\n        }, 200);\n        \n        // Function to set up copy buttons\n        function setupCopyButtons() {\n            document.querySelectorAll('.copy-button').forEach(function(button) {\n                button.addEventListener('click', function() {\n                    // Store the current button ID\n                    var buttonId = this.id;\n                    var codeId = this.getAttribute('data-code-id');\n                    var codeElement = document.getElementById(codeId);\n                    var codeText = codeElement.textContent;\n                    \n                    // Create a temporary textarea element to copy from\n                    var textarea = document.createElement('textarea');\n                    textarea.value = codeText;\n                    textarea.setAttribute('readonly', '');\n                    textarea.style.position = 'absolute';\n                    textarea.style.left = '-9999px';\n                    document.body.appendChild(textarea);\n                    \n                    // Select and copy the text\n                    textarea.select();\n                    document.execCommand('copy');\n                    \n                    // Remove the temporary element\n                    document.body.removeChild(textarea);\n                    \n                    // Visual feedback - only for this specific button\n                    var originalText = this.innerHTML;\n                    this.innerHTML = '" + Chr(60) + "i class=" + Chr(34) + "fas fa-check" + Chr(34) + "" + Chr(62) + "" + Chr(60) + "/i" + Chr(62) + " Copied!';\n                    this.classList.add('copy-success');\n                    \n                    // Reset button after 5 seconds\n                    var buttonElement = this;\n                    setTimeout(function() {\n                        // Only reset if it hasn't been changed again\n                        if (buttonElement.classList.contains('copy-success')) {\n                            buttonElement.innerHTML = originalText;\n                            buttonElement.classList.remove('copy-success');\n                        }\n                    }, 5000);\n                });\n            });\n        }\n        \n        // Handle initial hash in URL if any\n        if (window.location.hash) {\n            var targetId = window.location.hash.substring(1);\n            var targetElement = document.getElementById(targetId);\n            if (targetElement) {\n                setTimeout(function() {\n                    targetElement.scrollIntoView({\n                        behavior: 'smooth'\n                    });\n                }, 100);\n            }\n        }\n    " + Chr(60) + "/script" + Chr(62) + "\n" + Chr(60) + "/body" + Chr(62) + "\n" + Chr(60) + "/html" + Chr(62) + "";
    if (mode == "md") {
        outDocs = outMDup + outMD;
    } else {
        outDocs = htmlUP + Chr(10) + outMDup + outMD + Chr(10) + htmlDOWN;
    }
    return outDocs;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
if (HTVM_getLang_HTVM() != "js") {
    DOCS_params = Trim(GetParams());
    if (Trim(StrSplit(DOCS_params, "\n", 1)) == "") {
        print("Usage: <instruction_file> [function_name]" + Chr(10) + Chr(10) + "- <instruction_file>: Required. Generates DOCUMENTATION.md and DOCUMENTATION.html." + Chr(10) + "- [function_name]: Optional. If provided, checks whether the function exists and it does not output any files.");
        print("no params Exiting...");
        ExitApp();
    }
    items17 = LoopParseFunc(DOCS_params, "\n", "\r")
    for (let A_Index17 = 0; A_Index17 < items17.length + 0; A_Index17++) {
        const A_LoopField17 = items17[A_Index17 - 0];
        if (A_Index17 == 0) {
            print(A_LoopField17);
            DOCS_param1 = Trim(A_LoopField17);
        }
        if (A_Index17 == 1) {
            print(A_LoopField17);
            DOCS_param2 = Trim(A_LoopField17);
        }
    }
    if (!FileExist(DOCS_param1)) {
        print("the file doesn't exist!!!");
        ExitApp();
    }
    if (Trim(DOCS_param2) != "") {
        DOCS_checkIfFuncNameExists = 1;
    }
    instructionFileData = FileRead(Trim(DOCS_param1));
    OUTdocs_HTML = genDocs("html");
    OUTdocs_MD = genDocs("md");
    FileDelete("DOCUMENTATION.md");
    FileAppend(OUTdocs_MD, "DOCUMENTATION.md");
    print("Everything is saved in DOCUMENTATION.md");
    print("========================================");
    FileDelete("DOCUMENTATION.html");
    FileAppend(OUTdocs_HTML, "DOCUMENTATION.html");
    print("Everything is saved in DOCUMENTATION.html");
    print("========================================");
    print("Done!");
}
// else add the full user instruction file in instructionFileData variable
// make sure to reset all vars
/*
var "";
var "";
var "";
var "";
var 0;
var "";
var "";
*/
// MAKE SURE to put the instruction file in instructionFileData variable!!!
// run genDocs("html") and the output will be text that needs to be saved in DOCUMENTATION.html
// run genDocs("md") and the output will be text that needs to be saved in DOCUMENTATION.md
