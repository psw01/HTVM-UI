#include <algorithm>
#include <any>
#include <cctype>
#include <cmath>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <unordered_set>
#include <vector>

// Function to escape special characters for regex
std::string escapeRegex(const std::string& str) {
    static const std::regex specialChars{R"([-[\]{}()*+?.,\^$|#\s])"};
    return std::regex_replace(str, specialChars, R"(\$&)");
}
// Function to split a string based on delimiters
std::vector<std::string> LoopParseFunc(const std::string& var, const std::string& delimiter1 = "", const std::string& delimiter2 = "") {
    std::vector<std::string> items;
    if (delimiter1.empty() && delimiter2.empty()) {
        // If no delimiters are provided, return a list of characters
        for (char c : var) {
            items.push_back(std::string(1, c));
        }
    } else {
        // Escape delimiters for regex
        std::string escapedDelimiters = escapeRegex(delimiter1 + delimiter2);
        // Construct the regular expression pattern for splitting the string
        std::string pattern = "[" + escapedDelimiters + "]+";
        std::regex regexPattern(pattern);
        std::sregex_token_iterator iter(var.begin(), var.end(), regexPattern, -1);
        std::sregex_token_iterator end;
        while (iter != end) {
            items.push_back(*iter++);
        }
    }
    return items;
}

// Print function for const char* specifically
void print(const char* value) {
    std::cout << std::string(value) << std::endl;  // Convert const char* to std::string
}
// Print function that converts all types to string if needed
template <typename T>
void print(const T& value) {
    if constexpr (std::is_same_v<T, std::string>) {
        std::cout << value << std::endl;
    } else if constexpr (std::is_same_v<T, char>) {
        std::cout << value << std::endl;
    } else if constexpr (std::is_same_v<T, int>) {
        std::cout << std::to_string(value) << std::endl;
    } else if constexpr (std::is_same_v<T, float>) {
        std::cout << std::to_string(value) << std::endl;
    } else if constexpr (std::is_same_v<T, double>) {
        std::cout << std::to_string(value) << std::endl;
    } else if constexpr (std::is_same_v<T, size_t>) {
        std::cout << std::to_string(value) << std::endl;
    } else if constexpr (std::is_same_v<T, bool>) {
        std::cout << (value ? "1" : "0") << std::endl;
    } else {
        std::cout << "Unsupported type" << std::endl;
    }
}

// Convert std::string to int
int INT(const std::string& str) {
    std::istringstream iss(str);
    int value;
    iss >> value;
    return value;
}

// Convert various types to std::string
std::string STR(int value) {
    return std::to_string(value);
}
// Convert various types to std::string
std::string STR(long long value) {
    return std::to_string(value);
}
std::string STR(float value) {
    return std::to_string(value);
}
std::string STR(double value) {
    return std::to_string(value);
}
std::string STR(size_t value) {
    return std::to_string(value);
}
std::string STR(bool value) {
    return value ? "1" : "0";
}
std::string STR(const char* value) {
    return std::string(value);
}

// Convert std::string to float
float FLOAT(const std::string& str) {
    std::istringstream iss(str);
    float value;
    iss >> value;
    return value;
}

// Function to find the position of needle in haystack (std::string overload)
int InStr(const std::string& haystack, const std::string& needle) {
    size_t pos = haystack.find(needle);
    return (pos != std::string::npos) ? static_cast<int>(pos) + 1 : 0;
}

// Function to get input from the user, similar to Python's input() function
std::string input(const std::string& prompt) {
    std::string userInput;
    std::cout << prompt; // Display the prompt to the user
    std::getline(std::cin, userInput); // Get the entire line of input
    return userInput;
}

std::string FileRead(const std::string& path) {
    std::ifstream file;
    std::filesystem::path full_path;
    // Check if the file path is an absolute path
    if (std::filesystem::path(path).is_absolute()) {
        full_path = path;
    } else {
        // If it's not a full path, prepend the current working directory
        full_path = std::filesystem::current_path() / path;
    }
    // Open the file
    file.open(full_path);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Could not open the file.");
    }
    // Read the file content into a string
    std::string content;
    std::string line;
    while (std::getline(file, line)) {
        content += line + '\n';
    }
    file.close();
    return content;
}

bool FileAppend(const std::string& content, const std::string& path) {
    std::ofstream file;
    // Open the file in append mode
    file.open(path, std::ios::app);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file for appending." << std::endl;
        return false;
    }
    // Append the content to the file
    file << content;
    // Close the file
    file.close();
    return true;
}

bool FileDelete(const std::string& path) {
    std::filesystem::path file_path(path);
    // Check if the file exists
    if (!std::filesystem::exists(file_path)) {
        return false;
    }
    // Attempt to remove the file
    if (!std::filesystem::remove(file_path)) {
        return false;
    }
    return true;
}

size_t StrLen(const std::string& str) {
    return str.length();
}

double Exp(double value) {
    return std::exp(value);
}

double Log(double value) {
    return std::log10(value);
}

std::string SubStr(const std::string& str, int startPos, int length = -1) {
    std::string result;
    size_t strLen = str.size();
    // Handle negative starting positions
    if (startPos < 0) {
        startPos += strLen;
        if (startPos < 0) startPos = 0;
    } else {
        if (startPos > static_cast<int>(strLen)) return ""; // Starting position beyond string length
        startPos -= 1; // Convert to 0-based index
    }
    // Handle length
    if (length < 0) {
        length = strLen - startPos; // Length to end of string
    } else if (startPos + length > static_cast<int>(strLen)) {
        length = strLen - startPos; // Adjust length to fit within the string
    }
    // Extract substring
    result = str.substr(startPos, length);
    return result;
}

std::string Trim(const std::string &inputString) {
    if (inputString.empty()) return "";
    size_t start = inputString.find_first_not_of(" \t\n\r\f\v");
    size_t end = inputString.find_last_not_of(" \t\n\r\f\v");
    return (start == std::string::npos) ? "" : inputString.substr(start, end - start + 1);
}

std::string StrReplace(const std::string &originalString, const std::string &find, const std::string &replaceWith) {
    std::string result = originalString;
    size_t pos = 0;
    while ((pos = result.find(find, pos)) != std::string::npos) {
        result.replace(pos, find.length(), replaceWith);
        pos += replaceWith.length();
    }
    return result;
}

std::string StringTrimLeft(const std::string &input, int numChars) {
    return (numChars <= input.length()) ? input.substr(numChars) : input;
}

std::string StringTrimRight(const std::string &input, int numChars) {
    return (numChars <= input.length()) ? input.substr(0, input.length() - numChars) : input;
}

std::string StrLower(const std::string &string) {
    std::string result = string;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

std::string StrSplit(const std::string &inputStr, const std::string &delimiter, int num) {
    size_t start = 0, end = 0, count = 0;
    while ((end = inputStr.find(delimiter, start)) != std::string::npos) {
        if (++count == num) {
            return inputStr.substr(start, end - start);
        }
        start = end + delimiter.length();
    }
    if (count + 1 == num) {
        return inputStr.substr(start);
    }
    return "";
}

std::string Chr(int number) {
    return (number >= 0 && number <= 0x10FFFF) ? std::string(1, static_cast<char>(number)) : "";
}

int Mod(int dividend, int divisor) {
    return dividend % divisor;
}

// Helper function to trim whitespace from both ends of a string
std::string trim(const std::string& str) {
    const std::string whitespace = " \t\n\r\f\v";
    size_t start = str.find_first_not_of(whitespace);
    if (start == std::string::npos) return "";
    size_t end = str.find_last_not_of(whitespace);
    return str.substr(start, end - start + 1);
}
// Helper function to convert string to lowercase
std::string toLower(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}
// Function to sort case-insensitively but ensure lowercase items come last
bool customSortCompare(const std::string& a, const std::string& b) {
    std::string lowerA = toLower(a);
    std::string lowerB = toLower(b);
    if (lowerA == lowerB) {
        // If case-insensitive equivalent, ensure lowercase items come last
        if (std::islower(a[0]) && std::isupper(b[0])) {
            return false; // a should come after b
        } else if (std::isupper(a[0]) && std::islower(b[0])) {
            return true; // a should come before b
        }
        return a < b; // Otherwise, sort lexicographically
    }
    return lowerA < lowerB;
}
// Function to remove exact duplicates (case-sensitive)
std::vector<std::string> removeExactDuplicates(const std::vector<std::string>& items) {
    std::unordered_set<std::string> seen;
    std::vector<std::string> uniqueItems;
    for (const auto& item : items) {
        if (seen.find(item) == seen.end()) {
            seen.insert(item);
            uniqueItems.push_back(item);
        }
    }
    return uniqueItems;
}
// Main sorting function
std::string Sort(const std::string& input, const std::string& options) {
    std::string delimiter = "\n";
    bool caseInsensitive = options.find('C') != std::string::npos;
    bool unique = options.find('U') != std::string::npos;
    bool reverse = options.find('R') != std::string::npos;
    bool random = options.find("Random") != std::string::npos;
    bool numeric = options.find('N') != std::string::npos;
    // Custom delimiter
    if (options.find('D') != std::string::npos) {
        size_t delimiterPos = options.find('D') + 1;
        if (delimiterPos < options.size()) {
            delimiter = options.substr(delimiterPos, 1);
        }
    }
    // Split input by delimiter
    std::vector<std::string> items;
    std::stringstream ss(input);
    std::string item;
    while (std::getline(ss, item, delimiter[0])) {
        item = trim(item);  // Trim whitespace from each item
        if (!item.empty()) {
            items.push_back(item);
        }
    }
    // Sort items
    if (numeric) {
        std::sort(items.begin(), items.end(), [](const std::string& a, const std::string& b) {
            return std::stoi(a) < std::stoi(b);
        });
    } else {
        std::sort(items.begin(), items.end(), customSortCompare);
    }
    // Remove exact duplicates if needed
    if (unique) {
        items = removeExactDuplicates(items);
    }
    // Apply reverse order if needed
    if (reverse) {
        std::reverse(items.begin(), items.end());
    }
    // Separate uppercase and lowercase items
    std::vector<std::string> uppercaseItems;
    std::vector<std::string> lowercaseItems;
    
    for (const auto& item : items) {
        if (std::isupper(item[0])) {
            uppercaseItems.push_back(item);
        } else {
            lowercaseItems.push_back(item);
        }
    }
    // Combine sorted uppercase items with sorted lowercase items
    std::string result;
    for (const auto& item : uppercaseItems) {
        result += item;
        result += delimiter;
    }
    for (const auto& item : lowercaseItems) {
        result += item;
        if (&item != &lowercaseItems.back()) {
            result += delimiter;
        }
    }
    // Remove trailing delimiter if necessary
    if (!result.empty() && result.back() == delimiter[0]) {
        result.pop_back();
    }
    return result;
}

std::string RegExReplace(const std::string& inputStr, const std::string& regexPattern, const std::string& replacement) {
    std::regex re(regexPattern, std::regex_constants::ECMAScript | std::regex_constants::multiline);
    return std::regex_replace(inputStr, re, replacement);
}

int RegExMatch(const std::string& haystack, const std::string& needle) {
    std::regex re(needle);
    std::smatch match;
    if (std::regex_search(haystack, match, re)) {
        return match.position(0) + 1; // 1-based index
    }
    return 0; // No match
}

// Overload for counting a single character
int countChars(const std::string& str, char theChar) {
    int count = 0;
    for (char c : str) {
        if (c == theChar) {
            count++;
        }
    }
    return count;
}
// Overload for counting a substring
int countChars(const std::string& str, const std::string& substring) {
    if (substring.empty()) return 0; // Avoid infinite loop
    int count = 0;
    size_t pos = 0;
    // Find occurrences of the substring
    while ((pos = str.find(substring, pos)) != std::string::npos) {
        count++;
        pos += substring.length(); // Move past the found substring
    }
    return count;
}

std::string HTVM_getLang_HTVM() {
    return "cpp";
}

bool noParams = false;
std::string allArgs = "";
// in allArgs will look like:
// full/path/code/
// HTVM-Instruction.txt file
// lang to convert to
// HTVM-Instruction.txt file MORE
// HTVM-Instruction.txt file MORE
// HTVM-Instruction.txt file MORE and more
#ifdef _WIN32
    #define ARGC __argc
    #define ARGV __argv
#else
    extern char **environ;
    int ARGC;
    char** ARGV;
    __attribute__((constructor)) void init_args(int argc, char* argv[], char* envp[]) {
        ARGC = argc;
        ARGV = argv;
    }
#endif
std::string GetParams() {
    std::vector<std::string> params;
    for (int i = 1; i < ARGC; ++i) {
        std::string arg = ARGV[i];
        if (std::filesystem::exists(arg)) {
            arg = std::filesystem::absolute(arg).string();
        }
        params.push_back(arg);
    }
    std::string result;
    for (const auto& param : params) {
        result += param + "\n";
    }
    return result;
}
void HTVM_v2_HTVM() {
    std::string params = Trim(GetParams());
    if (params == "") {
	noParams = true;
        print("Usage: HTVM <yourCodeFileName.yourExtension> <HTVM-instructions.txt> [optional LangToTranspileTo]\n\nOptions:\n  <yourCodeFileName.yourExtension>  The source code file to transpile.\n  <HTVM-instructions.txt>              The instructions file for transpilation.\n  [LangToTranspileTo]                Optional: Specify the target language (cpp, py, js, go, lua, cs, java, kt, rb, nim, ahk, swift, dart, ts, groovy, htvm or <yourExtension>).\n\nExample:\n  HTVM main.htvm HTVM-instructions.txt cpp\n");
        return;
    }
    std::vector<std::string> items1 = LoopParseFunc(params, "\n", "\r");
    for (size_t A_Index1 = 0; A_Index1 < items1.size() + 0; A_Index1++) {
        std::string A_LoopField1 = items1[A_Index1 - 0];
        allArgs += Trim(A_LoopField1) + "\n";
    }
    allArgs = StringTrimRight(allArgs, 1);
}



std::string str0 = "nothing";
std::string str00 = "nothing";
std::string str1 = "";
std::string str2 = "";
std::string str3 = "";
std::string str4 = "";
std::string str5 = "";
std::string str6 = "";
std::string str7 = "";
std::string str8 = "";
std::string str9 = "";
std::string str10 = "";
std::string str11 = "";
std::string str12 = "";
std::string str13 = "";
std::string str14 = "";
std::string str15 = "";
std::string str16 = "";
std::string str17 = "";
std::string str18 = "";
std::string str19 = "";
std::string str20 = "";
int int0 = 0;
int int1 = 0;
int int2 = 0;
int int3 = 0;
int int4 = 0;
int int5 = 0;
int int6 = 0;
int int7 = 0;
std::vector<std::string> argHTVMinstrMORE;
int isNotHTVMfileEXTRA_INT = 0;
int isNotHTVMfile2 = 0;
std::string isNotHTVMfileEXTRA_LIB_INFO = "";
std::string isNotHTVMfileEXTRA_FUNCS_INFO = "";
std::vector<std::string> programmingBlock_InTheTranspiledLang;
std::vector<std::string> programmingBlock_CPP;
std::vector<std::string> programmingBlock_PY;
std::vector<std::string> programmingBlock_JS;
std::vector<std::string> programmingBlock_GO;
std::vector<std::string> programmingBlock_LUA;
std::vector<std::string> programmingBlock_CS;
std::vector<std::string> programmingBlock_JAVA;
std::vector<std::string> programmingBlock_KT;
std::vector<std::string> programmingBlock_RB;
std::vector<std::string> programmingBlock_NIM;
std::vector<std::string> programmingBlock_AHK;
std::vector<std::string> programmingBlock_SWIFT;
std::vector<std::string> programmingBlock_DART;
std::vector<std::string> programmingBlock_TS;
std::vector<std::string> programmingBlock_GROOVY;
std::vector<std::string> programmingBlock_HTVM;
std::vector<std::string> programmingBlock_HTVMsyntax;
std::vector<std::string> fullLangAllOperators;
std::vector<std::string> fullLangAllOperators_HELP;
int fixExpertionLineFuncOnly = 0;
std::string langToConvertTo = "";
std::string langFileExtension = "";
std::string commands = "";
std::string keyWordAlliance = "";
std::string keyWordCrew = "";
std::string keyWordMethod = "";
std::string keyWordDefObj = "";
std::string keyWordPorp = "";
std::string keyWordThis = "";
std::string keyWordInclude = "";
std::string keyWordCodeInTheTranspiledLangStart = "";
std::string keyWordCodeInTheTranspiledLangEnd = "";
std::string keyWordCodeInTheTranspiledLangStartCPP = "";
std::string keyWordCodeInTheTranspiledLangEndCPP = "";
std::string keyWordCodeInTheTranspiledLangStartPY = "";
std::string keyWordCodeInTheTranspiledLangEndPY = "";
std::string keyWordCodeInTheTranspiledLangStartJS = "";
std::string keyWordCodeInTheTranspiledLangEndJS = "";
std::string keyWordCodeInTheTranspiledLangStartGO = "";
std::string keyWordCodeInTheTranspiledLangEndGO = "";
std::string keyWordCodeInTheTranspiledLangStartLUA = "";
std::string keyWordCodeInTheTranspiledLangEndLUA = "";
std::string keyWordCodeInTheTranspiledLangStartCS = "";
std::string keyWordCodeInTheTranspiledLangEndCS = "";
std::string keyWordCodeInTheTranspiledLangStartJAVA = "";
std::string keyWordCodeInTheTranspiledLangEndJAVA = "";
std::string keyWordCodeInTheTranspiledLangStartKT = "";
std::string keyWordCodeInTheTranspiledLangEndKT = "";
std::string keyWordCodeInTheTranspiledLangStartRB = "";
std::string keyWordCodeInTheTranspiledLangEndRB = "";
std::string keyWordCodeInTheTranspiledLangStartNIM = "";
std::string keyWordCodeInTheTranspiledLangEndNIM = "";
std::string keyWordCodeInTheTranspiledLangStartAHK = "";
std::string keyWordCodeInTheTranspiledLangEndAHK = "";
std::string keyWordCodeInTheTranspiledLangStartSWIFT = "";
std::string keyWordCodeInTheTranspiledLangEndSWIFT = "";
std::string keyWordCodeInTheTranspiledLangStartDART = "";
std::string keyWordCodeInTheTranspiledLangEndDART = "";
std::string keyWordCodeInTheTranspiledLangStartTS = "";
std::string keyWordCodeInTheTranspiledLangEndTS = "";
std::string keyWordCodeInTheTranspiledLangStartGROOVY = "";
std::string keyWordCodeInTheTranspiledLangEndGROOVY = "";
std::string keyWordCodeInTheTranspiledLangStartHTVM = "";
std::string keyWordCodeInTheTranspiledLangEndHTVM = "";
std::string keyWordCodeInHTVMstart = "";
std::string keyWordCodeInHTVMend = "";
std::string keyWordCurlyBraceOpen = "";
std::string keyWordCurlyBraceClose = "";
std::string keyWordNull = "";
std::string keyWordTrue = "";
std::string keyWordFalse = "";
std::string keyWordVoid = "";
std::string keyWordDouble = "";
std::string keyWordChar = "";
std::string keyWordUint8 = "";
std::string keyWordUint16 = "";
std::string keyWordUint32 = "";
std::string keyWordUint64 = "";
std::string keyWordINT = "";
std::string keyWordSTR = "";
std::string keyWordBOOL = "";
std::string keyWordFLOAT = "";
std::string keyWordINT8 = "";
std::string keyWordINT16 = "";
std::string keyWordINT32 = "";
std::string keyWordINT64 = "";
std::string keyWordIF = "";
std::string keyWordElseIf = "";
std::string keyWordElse = "";
std::string keyWordWhileLoop = "";
std::string keyWordLoopInfinite = "";
std::string keyWordLoop = "";
std::string keyWordLoopParse = "";
std::string keyWordContinue = "";
std::string keyWordBreak = "";
std::string keyWordFunc = "";
std::string keyWordAwait = "";
std::string keyWordAsync = "";
std::string keyWordThrow = "";
std::string keyWordErrorMsg = "";
std::string keyWordTry = "";
std::string keyWordCatch = "";
std::string keyWordFinally = "";
std::string keyWordReturnStatement = "";
std::string keyWordArrayAppend = "";
std::string keyWordArrayPop = "";
std::string keyWordArraySize = "";
std::string keyWordArrayInsert = "";
std::string keyWordArrayRemove = "";
std::string keyWordArrayIndexOf = "";
std::string keyWordArrayDefinition = "";
std::string keyWordArrayOfIntegersDefinition = "";
std::string keyWordArrayOfStringsDefinition = "";
std::string keyWordArrayOfFloatingPointNumbersDefinition = "";
std::string keyWordArrayOfBooleansDefinition = "";
std::string keyWordVar = "";
std::string keyWordLet = "";
std::string keyWordConst = "";
std::string keyWordEnd = "";
std::string keyWordGlobal = "";
std::string keyWordComment = "";
std::string keyWordCommentOpenMultiLine = "";
std::string keyWordCommentCloseMultiLine = "";
std::string keyWordEscpaeChar = "";
std::string keyWordMainLabel = "";
std::string keyWordConcat = "";
std::string keyWordAdd = "";
std::string keyWordSub = "";
std::string keyWordMul = "";
std::string keyWordDiv = "";
std::string keyWordMod = "";
std::string keyWordExp = "";
std::string keyWordEqual = "";
std::string keyWordStrictEqual = "";
std::string keyWordNotEqual = "";
std::string keyWordGreater = "";
std::string keyWordLess = "";
std::string keyWordGreaterEqual = "";
std::string keyWordLessEqual = "";
std::string keyWordAnd = "";
std::string keyWordOr = "";
std::string keyWordNot = "";
std::string keyWordBitAnd = "";
std::string keyWordBitOr = "";
std::string keyWordBitXor = "";
std::string keyWordBitNot = "";
std::string keyWordShiftLeft = "";
std::string keyWordShiftRight = "";
std::string keyWordShiftUnsignedRight = "";
std::string keyWordAssign = "";
std::string keyWordAssignAdd = "";
std::string keyWordAssignConcat = "";
std::string keyWordAssignSub = "";
std::string keyWordAssignMul = "";
std::string keyWordAssignDiv = "";
std::string keyWordAssignMod = "";
std::string keyWordAssignShiftLeft = "";
std::string keyWordAssignShiftRight = "";
std::string keyWordLogicalAssignShiftRight = "";
std::string keyWordAssignBitAnd = "";
std::string keyWordAssignBitOr = "";
std::string keyWordAssignBitXor = "";
std::string keyWordTernary1 = "";
std::string keyWordTernary2 = "";
std::string keyWordInc = "";
std::string keyWordDec = "";
std::string AHKlikeLoopsIndexedAt = "";
std::string keyWordAIndex = "";
std::string keyWordALoopField = "";
std::string useFuncKeyWord = "";
std::string useCurlyBraces = "";
std::string useEnd = "";
std::string useSemicolon = "";
std::string theSemicolon = "";
std::string theColon = "";
std::string useParentheses = "";
std::string usePrefixTypeForTypeDefinition = "";
std::string usePostfixTypeForTypeDefinition = "";
std::string usePythonicColonSyntax = "";
std::string useCurlyBracesSyntaxForArrayDef = "";
std::string useInJavaScriptAlwaysUseVar = "";
std::string useJavaScriptInAfullHTMLfile = "";
std::string useJavaScriptAmainFuncDef = "";
std::string useJavaScriptAllFuncsAreAsync = "";
std::string useJavaScriptAlwaysTripleEqual = "";
std::string langToConvertTo_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string langFileExtension_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string commands_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordAlliance_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCrew_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordMethod_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordDefObj_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordPorp_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordThis_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordInclude_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangStart_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangEnd_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangStartCPP_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangEndCPP_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangStartPY_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangEndPY_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangStartJS_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangEndJS_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangStartGO_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangEndGO_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangStartLUA_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangEndLUA_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangStartCS_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangEndCS_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangStartJAVA_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangEndJAVA_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangStartKT_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangEndKT_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangStartRB_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangEndRB_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangStartNIM_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangEndNIM_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangStartAHK_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangEndAHK_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangStartSWIFT_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangEndSWIFT_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangStartDART_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangEndDART_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangStartTS_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangEndTS_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangStartGROOVY_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangEndGROOVY_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangStartHTVM_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInTheTranspiledLangEndHTVM_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInHTVMstart_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCodeInHTVMend_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCurlyBraceOpen_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCurlyBraceClose_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordNull_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordTrue_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordFalse_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordVoid_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordDouble_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordChar_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordUint8_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordUint16_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordUint32_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordUint64_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordINT_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordSTR_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordBOOL_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordFLOAT_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordINT8_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordINT16_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordINT32_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordINT64_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordIF_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordElseIf_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordElse_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordWhileLoop_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordLoopInfinite_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordLoop_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordLoopParse_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordContinue_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordBreak_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordFunc_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordAwait_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordAsync_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordThrow_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordErrorMsg_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordTry_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCatch_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordFinally_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordReturnStatement_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordArrayAppend_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordArrayPop_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordArraySize_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordArrayInsert_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordArrayRemove_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordArrayIndexOf_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordArrayDefinition_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordArrayOfIntegersDefinition_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordArrayOfStringsDefinition_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordArrayOfFloatingPointNumbersDefinition_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordArrayOfBooleansDefinition_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordVar_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordLet_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordConst_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordEnd_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordGlobal_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordComment_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCommentOpenMultiLine_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordCommentCloseMultiLine_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordEscpaeChar_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordMainLabel_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordConcat_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordAdd_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordSub_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordMul_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordDiv_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordMod_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordExp_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordEqual_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordStrictEqual_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordNotEqual_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordGreater_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordLess_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordGreaterEqual_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordLessEqual_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordAnd_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordOr_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordNot_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordBitAnd_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordBitOr_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordBitXor_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordBitNot_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordShiftLeft_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordShiftRight_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordShiftUnsignedRight_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordAssign_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordAssignAdd_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordAssignConcat_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordAssignSub_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordAssignMul_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordAssignDiv_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordAssignMod_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordAssignShiftLeft_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordAssignShiftRight_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordLogicalAssignShiftRight_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordAssignBitAnd_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordAssignBitOr_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordAssignBitXor_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordTernary1_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordTernary2_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordInc_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordDec_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string AHKlikeLoopsIndexedAt_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordAIndex_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string keyWordALoopField_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string useCurlyBraces_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string useEnd_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string useSemicolon_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string useParentheses_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string usePrefixTypeForTypeDefinition_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string usePostfixTypeForTypeDefinition_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string usePythonicColonSyntax_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string useCurlyBracesSyntaxForArrayDef_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string useInJavaScriptAlwaysUseVar_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string useJavaScriptInAfullHTMLfile_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string useJavaScriptAmainFuncDef_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string useJavaScriptAllFuncsAreAsync_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string useJavaScriptAlwaysTripleEqual_2 = "awesdgfd-awesrs-awedsfd-aesdg-sc-zsdxfvc-sdfd";
std::string out_KeyWordsCommands = "";
std::string outTrimCode = "";
std::string htCode = "";
std::string outVarOperator = "";
int lineDone = 0;
int areWeInAFuncFromInstructions = 0;
int areWeInAFuncFromInstructionsLineNum = 0;
int javaMainFuncSeen = 0;
std::string theTryCatchVarForErrors = "jhku-dfsds-ds-d-ffdsf-sdfsfdsedsf";
std::string theJSvarDeclaredVarsBugFix = "|";
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
std::string KeyWordsCommands(std::string theCodeCommands, std::string mode, std::string keyWordsCommands, std::string langToConvertTo) {
    theCodeCommands = StrReplace(theCodeCommands, "%", "");
    if (mode == "check") {
        std::vector<std::string> items1 = LoopParseFunc(keyWordsCommands, "|");
        for (size_t A_Index1 = 0; A_Index1 < items1.size() + 0; A_Index1++) {
            std::string A_LoopField1 = items1[A_Index1 - 0];
            std::vector<std::string> items2 = LoopParseFunc(A_LoopField1, ",");
            for (size_t A_Index2 = 0; A_Index2 < items2.size() + 0; A_Index2++) {
                std::string A_LoopField2 = items2[A_Index2 - 0];
                if (A_Index2 == 0) {
                    if (SubStr(StrLower(theCodeCommands), 1, StrLen(A_LoopField2 + ", ")) == StrLower(A_LoopField2 + ", ")) {
                        //MsgBox, true
                        return "true";
                    }
                }
                if (A_Index2 == 0) {
                    if (theCodeCommands == A_LoopField2) {
                        //MsgBox, true
                        return "true";
                    }
                }
            }
        }
        //MsgBox, false
        return "false";
    }
    int AIndex = 0;
    if (mode == "transpile") {
        int keyWordsCommandsNumLine = 1;
        std::vector<std::string> items3 = LoopParseFunc(keyWordsCommands, "|");
        for (size_t A_Index3 = 0; A_Index3 < items3.size() + 0; A_Index3++) {
            std::string A_LoopField3 = items3[A_Index3 - 0];
            AIndex = A_Index3;
            std::vector<std::string> items4 = LoopParseFunc(A_LoopField3, ",");
            for (size_t A_Index4 = 0; A_Index4 < items4.size() + 0; A_Index4++) {
                std::string A_LoopField4 = items4[A_Index4 - 0];
                if (A_Index4 == 0) {
                    if (SubStr(StrLower(theCodeCommands), 1, StrLen(A_LoopField4 + ", ")) == StrLower(A_LoopField4 + ", ")) {
                        //MsgBox, true
                        keyWordsCommandsNumLine = AIndex;
                        break;
                    }
                }
                if (A_Index4 == 0) {
                    //MsgBox, %theCodeCommands% = %A_LoopField4%
                    if (theCodeCommands == A_LoopField4) {
                        //MsgBox, true
                        keyWordsCommandsNumLine = AIndex;
                        break;
                    }
                }
            }
        }
        std::string outConstuctTheOutFromTheCommands = "";
        std::string outConstuctTheOutFromTheCommandsFucnName = "";
        std::string outConstuctTheOutFromTheCommandsParams = "";
        std::string outConstuctTheOutFromTheCommandsOutVar = "";
        std::string outConstuctTheOutFromTheCommandsInVar = "";
        int theCodeCommandNum = 0;
        int outConstuctTheOutFromTheCommandsLineTranspile = 0;
        std::string outConstuctTheOutFromTheCommandsLineTranspileText = "";
        std::string semicolon = "";
        if (langToConvertTo != "py" && langToConvertTo != "nim" && langToConvertTo != "ahk" && langToConvertTo != "go" && langToConvertTo != "lua" && langToConvertTo != "kt" && langToConvertTo != "rb" && langToConvertTo != "swift" && langToConvertTo != "groovy") {
            semicolon = ";";
        }
        std::vector<std::string> theCodeCommand;
        theCodeCommands = Trim(theCodeCommands);
        std::vector<std::string> items5 = LoopParseFunc(theCodeCommands, ",");
        for (size_t A_Index5 = 0; A_Index5 < items5.size() + 0; A_Index5++) {
            std::string A_LoopField5 = items5[A_Index5 - 0];
            theCodeCommand.push_back(Trim(A_LoopField5));
            //MsgBox, % A_LoopField5
        }
        std::vector<std::string> items6 = LoopParseFunc(keyWordsCommands, "|");
        for (size_t A_Index6 = 0; A_Index6 < items6.size() + 0; A_Index6++) {
            std::string A_LoopField6 = items6[A_Index6 - 0];
            if (keyWordsCommandsNumLine == A_Index6) {
                //MsgBox, % A_LoopField6
                std::vector<std::string> items7 = LoopParseFunc(A_LoopField6, ",");
                for (size_t A_Index7 = 0; A_Index7 < items7.size() + 0; A_Index7++) {
                    std::string A_LoopField7 = items7[A_Index7 - 0];
                    if (A_Index7 == 0) {
                        outConstuctTheOutFromTheCommandsFucnName = A_LoopField7;
                    }
                    else if (A_Index7 == 1) {
                        //MsgBox, % A_LoopField7
                        if (A_LoopField7 == "lineTranspile") {
                            outConstuctTheOutFromTheCommandsLineTranspile = 1;
                        }
                        if (A_LoopField7 == "OUTVAR") {
                            outConstuctTheOutFromTheCommandsOutVar = theCodeCommand[theCodeCommandNum];
                        }
                        else if (A_LoopField7 == "INOUTVAR") {
                            outConstuctTheOutFromTheCommandsOutVar = theCodeCommand[theCodeCommandNum];
                            outConstuctTheOutFromTheCommandsInVar = theCodeCommand[theCodeCommandNum];
                        }
                        else if (A_LoopField7 == "INVAR") {
                            outConstuctTheOutFromTheCommandsInVar = theCodeCommand[theCodeCommandNum];
                        } else {
                            if (InStr(A_LoopField7, Chr(39))) {
                                outConstuctTheOutFromTheCommandsParams += Chr(34) + theCodeCommand[theCodeCommandNum] + Chr(34) + ", ";
                            } else {
                                outConstuctTheOutFromTheCommandsParams += theCodeCommand[theCodeCommandNum] + ", ";
                            }
                        }
                    }
                    else if (A_Index7 == 2) {
                        if (outConstuctTheOutFromTheCommandsLineTranspile == 1) {
                            outConstuctTheOutFromTheCommandsLineTranspileText = A_LoopField7;
                        }
                        if (A_LoopField7 == "INVAR") {
                            outConstuctTheOutFromTheCommandsInVar = theCodeCommand[theCodeCommandNum];
                        } else {
                            if (InStr(A_LoopField7, Chr(39))) {
                                outConstuctTheOutFromTheCommandsParams += Chr(34) + theCodeCommand[theCodeCommandNum] + Chr(34) + ", ";
                            } else {
                                outConstuctTheOutFromTheCommandsParams += theCodeCommand[theCodeCommandNum] + ", ";
                            }
                        }
                    } else {
                        //MsgBox, % theCodeCommand[theCodeCommandNum]
                        if (InStr(A_LoopField7, Chr(39))) {
                            if (Trim(theCodeCommand[theCodeCommandNum]) != "") {
                                outConstuctTheOutFromTheCommandsParams += Chr(34) + theCodeCommand[theCodeCommandNum] + Chr(34) + ", ";
                            }
                        } else {
                            if (Trim(theCodeCommand[theCodeCommandNum]) != "") {
                                outConstuctTheOutFromTheCommandsParams += theCodeCommand[theCodeCommandNum] + ", ";
                            }
                        }
                    }
                    theCodeCommandNum++;
                }
                break;
            }
        }
        outConstuctTheOutFromTheCommandsParams = StringTrimRight(outConstuctTheOutFromTheCommandsParams, 2);
        if (outConstuctTheOutFromTheCommandsOutVar != "") {
            if (outConstuctTheOutFromTheCommandsParams == "") {
                outConstuctTheOutFromTheCommands = outConstuctTheOutFromTheCommandsOutVar + " = " + outConstuctTheOutFromTheCommandsFucnName + "(" + outConstuctTheOutFromTheCommandsInVar + ")" + semicolon;
            } else {
                outConstuctTheOutFromTheCommands = outConstuctTheOutFromTheCommandsOutVar + " = " + outConstuctTheOutFromTheCommandsFucnName + "(" + outConstuctTheOutFromTheCommandsInVar + ", " + outConstuctTheOutFromTheCommandsParams + ")" + semicolon;
            }
        }
        if (outConstuctTheOutFromTheCommandsOutVar == "") {
            if (outConstuctTheOutFromTheCommandsParams == "") {
                outConstuctTheOutFromTheCommands = outConstuctTheOutFromTheCommandsFucnName + "(" + outConstuctTheOutFromTheCommandsInVar + ")" + semicolon;
            } else {
                outConstuctTheOutFromTheCommands = outConstuctTheOutFromTheCommandsFucnName + "(" + outConstuctTheOutFromTheCommandsInVar + ", " + outConstuctTheOutFromTheCommandsParams + ")" + semicolon;
            }
        }
        if (outConstuctTheOutFromTheCommandsLineTranspile == 1) {
            outConstuctTheOutFromTheCommands = outConstuctTheOutFromTheCommandsLineTranspileText;
        }
        outConstuctTheOutFromTheCommands = StrReplace(outConstuctTheOutFromTheCommands, "(, ", "( ");
        outConstuctTheOutFromTheCommands = StrReplace(outConstuctTheOutFromTheCommands, "(,", "(");
        return outConstuctTheOutFromTheCommands;
    }
    return "false";
}
std::string HTVMmatchStrRrplace(std::string line, std::string matchString, std::string replaceString) {
    std::string lineOut = "";
    if (!InStr(line, matchString)) {
        return line;
    }
    std::string allDelimiters = " ()[].,;:'!&|=<>+-*/^%~" + Chr(34) + Chr(9) + Chr(11);
    std::vector<std::string> lineArr;
    std::vector<std::string> items8 = LoopParseFunc(line);
    for (size_t A_Index8 = 0; A_Index8 < items8.size() + 0; A_Index8++) {
        std::string A_LoopField8 = items8[A_Index8 - 0];
        lineArr.push_back(A_LoopField8);
    }
    int matchStringLEN = StrLen(matchString);
    int replaceStringLEN = StrLen(replaceString);
    std::vector<int> allPosForReplacing;
    std::string sildingLine = "";
    int isStart = 1;
    int i1 = 0;
    int hasFound = 0;
    int hasFound2 = 0;
    int isStartTrue = 0;
    int isEndTrue = 0;
    // char1 is for text outside the start
    std::string char1 = "";
    // char2 is for text inside the start
    std::string char2 = "";
    // char3 is for text inside the end
    std::string char3 = "";
    // char4 is for text outside the end
    std::string char4 = "";
    int isMatch = 0;
    sildingLine = "";
    isStart = 1;
    i1 = 0;
    hasFound = 0;
    hasFound2 = 0;
    isStartTrue = 0;
    isEndTrue = 0;
    for (int A_Index9 = 0; A_Index9 < lineArr.size() + 0; A_Index9++) {
        char1 = "";
        char2 = "";
        char3 = "";
        char4 = "";
        isMatch = 0;
        if (A_Index9 != 0) {
            isStart = 0;
        }
        sildingLine = "";
        for (int A_Index10 = 0; A_Index10 < matchStringLEN + 0; A_Index10++) {
            if (A_Index10 + i1 <= lineArr.size() - 1) {
                sildingLine += lineArr[A_Index10 + i1];
            }
        }
        if (StrLen(sildingLine) < matchStringLEN) {
            break;
        }
        //print("!!!!111111111!!!!!!: " . sildingLine)
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;==================
        if (sildingLine == matchString) {
            hasFound = 1;
            if (isStart != 1) {
                //print("!!!!2222222222!!!!!!: " . lineArr[i1 - 1])
                char1 = lineArr[i1 - 1];
                //print("!!!!2222222222.555555555!!!!!!: " . lineArr[i1])
                char2 = lineArr[i1];
            } else {
                isStartTrue = 1;
            }
            if (i1 + matchStringLEN < lineArr.size()) {
                //print("!!!!3333333333.5555555555!!!!!!: " . lineArr[i1 + matchStringLEN - 1])
                char3 = lineArr[i1 + matchStringLEN - 1];
                //print("!!!!3333333333!!!!!!: " . lineArr[i1 + matchStringLEN])
                char4 = lineArr[i1 + matchStringLEN];
            } else {
                isEndTrue = 1;
            }
            if (InStr(allDelimiters, char1) || InStr(allDelimiters, char2)) {
                isStartTrue = 1;
            }
            if (InStr(allDelimiters, char3) || InStr(allDelimiters, char4)) {
                isEndTrue = 1;
            }
            if (isStartTrue == 1 && isEndTrue == 1) {
                isMatch = 1;
            }
        }
        //;;;;;;;;;;;;;;;;;;;===============
        if (isMatch == 1) {
            if (allPosForReplacing.size() > 0) {
                for (int A_Index11 = 0; A_Index11 < allPosForReplacing.size() + 0; A_Index11++) {
                    if (i1 + 1 != allPosForReplacing[A_Index11]) {
                        allPosForReplacing.push_back(i1 + 1);
                        break;
                    }
                }
            } else {
                allPosForReplacing.push_back(i1 + 1);
            }
        }
        i1++;
    }
    std::string lineTEMP = "";
    lineOut = line;
    //print(allPosForReplacing)
    if (allPosForReplacing.size() > 0) {
        // matchStringLEN
        // replaceStringLEN
        int l2 = 0;
        int currentPos = 0;
        int onceEnd = 0;
        for (int A_Index12 = 0; A_Index12 < allPosForReplacing.size() + 0; A_Index12++) {
            if (A_Index12 == 0) {
                currentPos = allPosForReplacing[A_Index12];
            } else {
                currentPos = allPosForReplacing[A_Index12] - (matchStringLEN - replaceStringLEN);
            }
            onceEnd = 0;
            std::vector<std::string> items13 = LoopParseFunc(lineOut);
            for (size_t A_Index13 = 0; A_Index13 < items13.size() + 0; A_Index13++) {
                std::string A_LoopField13 = items13[A_Index13 - 0];
                if (A_Index13 + 2 > currentPos && A_Index13 + 1 < currentPos + matchStringLEN) {
                    onceEnd++;
                    //print("DDDDDDDDDDD" . STR(A_Index13))
                    if (onceEnd == 1) {
                        lineTEMP += replaceString;
                    }
                } else {
                    lineTEMP += A_LoopField13;
                }
            }
            lineOut = lineTEMP;
            lineTEMP = "";
            //print(lineTEMP)
            l2++;
        }
    } else {
        return line;
    }
    return lineOut;
}
std::string SubStrLastChars(std::string text, int numOfChars) {
    std::string LastOut = "";
    int NumOfChars = 0;
    std::vector<std::string> items14 = LoopParseFunc(text);
    for (size_t A_Index14 = 0; A_Index14 < items14.size() + 0; A_Index14++) {
        std::string A_LoopField14 = items14[A_Index14 - 0];
        NumOfChars++;
    }
    for (int A_Index15 = 0; A_Index15 < numOfChars + 0; A_Index15++) {
        NumOfChars--;
    }
    std::vector<std::string> items16 = LoopParseFunc(text);
    for (size_t A_Index16 = 0; A_Index16 < items16.size() + 0; A_Index16++) {
        std::string A_LoopField16 = items16[A_Index16 - 0];
        if (A_Index16 >= NumOfChars) {
            LastOut += A_LoopField16;
        }
    }
    return LastOut;
}
std::string ExtractDigits(std::string inputString) {
    std::string digits = "";
    std::vector<std::string> items17 = LoopParseFunc(inputString);
    for (size_t A_Index17 = 0; A_Index17 < items17.size() + 0; A_Index17++) {
        std::string A_LoopField17 = items17[A_Index17 - 0];
        if (RegExMatch(A_LoopField17, "\\d")) {
            digits += A_LoopField17;
        }
    }
    return digits;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
// Helper function to create spaces
std::string spaces(int n) {
    std::string s = "";
    if (n != 0) {
        for (int A_Index18 = 0; A_Index18 < n + 0; A_Index18++) {
            s += " ";
        }
    }
    return s;
}
// Define the function to check odd spaces at the beginning
std::string CheckOddLeadingSpaces(std::string string123) {
    // Initialize a variable to count the spaces
    int spaceCount = 0;
    // Loop through the string one character at a time
    std::vector<std::string> items19 = LoopParseFunc(string123);
    for (size_t A_Index19 = 0; A_Index19 < items19.size() + 0; A_Index19++) {
        std::string A_LoopField19 = items19[A_Index19 - 0];
        // Check if the current character is a space
        if (A_LoopField19 == Chr(32)) {
            spaceCount++;
        } else {
            // When we hit a non-space character, break the loop
            break;
        }
    }
    // Return true if the number of spaces is odd, false otherwise
    std::string sdsfawasd = STR(Mod(spaceCount, 2) == 1);
    //MsgBox, % sdsfawasd
    return sdsfawasd;
}
std::string LTrim(std::string input) {
    std::string result = "";
    bool foundNonSpace = false;
    std::vector<std::string> items20 = LoopParseFunc(input);
    for (size_t A_Index20 = 0; A_Index20 < items20.size() + 0; A_Index20++) {
        std::string A_LoopField20 = items20[A_Index20 - 0];
        if (A_LoopField20 != " " || foundNonSpace) {
            result += A_LoopField20;
            foundNonSpace = true;
        }
    }
    return result;
}
std::string getLastChar(std::string strippedString) {
    std::string lastChar;
    std::vector<std::string> items21 = LoopParseFunc(strippedString);
    for (size_t A_Index21 = 0; A_Index21 < items21.size() + 0; A_Index21++) {
        std::string A_LoopField21 = items21[A_Index21 - 0];
        lastChar = A_LoopField21;
    }
    return lastChar;
}
std::string AddCurlyBraces(std::string pythonCode) {
    pythonCode = StrReplace(pythonCode, Chr(9), "    ");
    std::string result = "";
    int indentLevel = 0;
    int indent = 0;
    std::string line = "";
    std::string stripped = "";
    std::vector<std::string> items22 = LoopParseFunc(pythonCode, "\n", "\r");
    for (size_t A_Index22 = 0; A_Index22 < items22.size() + 0; A_Index22++) {
        std::string A_LoopField22 = items22[A_Index22 - 0];
        line = A_LoopField22;
        stripped = Trim(line);
        if (stripped == "") {
            result += line + "\n";
            continue;
        }
        // Count leading spaces
        indent = StrLen(line) - StrLen(LTrim(line));
        // Close braces for unindents
        for (int A_Index23 = 0; ; A_Index23++) {
            if (indentLevel <= indent) {
                break;
            }
            indentLevel -= 4;
            result += spaces(indentLevel) + "}\n";
        }
        // Add opening brace for new blocks
        if (getLastChar(stripped) == ":" && SubStr(StrLower(Trim(A_LoopField22)), 1, StrLen(StrLower(keyWordComment))) != StrLower(keyWordComment)) {
            result += SubStr(line, 1, -1) + " {\n";
            indentLevel += 4;
        } else {
            result += line + "\n";
        }
    }
    // Close any remaining open braces
    for (int A_Index24 = 0; ; A_Index24++) {
        if (indentLevel <= 0) {
            break;
        }
        indentLevel -= 4;
        result += spaces(indentLevel) + "}\n";
    }
    return result;
}
std::string RepeatSpaces(int count) {
    std::string spaces = "";
    for (int A_Index25 = 0; A_Index25 < count + 0; A_Index25++) {
        spaces += Chr(32);
    }
    return spaces;
}
std::string indent_nested_curly_braces(std::string input_string, int modeCurlyBracesOn) {
    int indent_size = 4;
    int current_indent = 0;
    std::string result = "";
    std::string trimmed_line = "";
    std::string resultOut = "";
    std::string culyOpenFix = "{";
    std::string culyCloseFix = "}";
    if (langToConvertTo == langFileExtension_2) {
        culyOpenFix = Trim(keyWordCurlyBraceOpen_2);
        culyCloseFix = Trim(keyWordCurlyBraceClose_2);
    }
    //MsgBox, % input_string
    std::vector<std::string> items26 = LoopParseFunc(input_string, "\n", "\r");
    for (size_t A_Index26 = 0; A_Index26 < items26.size() + 0; A_Index26++) {
        std::string A_LoopField26 = items26[A_Index26 - 0];
        trimmed_line = Trim(A_LoopField26);
        if (trimmed_line == Chr(123)) {
            result += Chr(32) + RepeatSpaces(current_indent) + trimmed_line + "\n";
            current_indent = current_indent + indent_size;
        }
        else if (trimmed_line == Chr(125)) {
            current_indent = current_indent - indent_size;
            result += Chr(32) + RepeatSpaces(current_indent) + trimmed_line + "\n";
        } else {
            result += Chr(32) + RepeatSpaces(current_indent) + trimmed_line + "\n";
        }
    }
    if (modeCurlyBracesOn == 0) {
        std::string resultOut = "";
        std::vector<std::string> items27 = LoopParseFunc(result, "\n", "\r");
        for (size_t A_Index27 = 0; A_Index27 < items27.size() + 0; A_Index27++) {
            std::string A_LoopField27 = items27[A_Index27 - 0];
            if (Trim(A_LoopField27) != "{" && Trim(A_LoopField27) != "}") {
                resultOut += A_LoopField27 + "\n";
            }
        }
        result = StringTrimRight(resultOut, 1);
    } else {
        // format curly braces in a K&R style
        std::vector<std::string> lookIntoFurture;
        std::vector<std::string> items28 = LoopParseFunc(result, "\n", "\r");
        for (size_t A_Index28 = 0; A_Index28 < items28.size() + 0; A_Index28++) {
            std::string A_LoopField28 = items28[A_Index28 - 0];
            lookIntoFurture.push_back(Trim(A_LoopField28));
        }
        lookIntoFurture.push_back(" ");
        std::string resultOut = "";
        int skipNext = 0;
        std::vector<std::string> items29 = LoopParseFunc(result, "\n", "\r");
        for (size_t A_Index29 = 0; A_Index29 < items29.size() + 0; A_Index29++) {
            std::string A_LoopField29 = items29[A_Index29 - 0];
            skipNext--;
            if (skipNext <= 0) {
                skipNext = 0;
            }
            if (Trim(lookIntoFurture[A_Index29 + 1]) == "{") {
                resultOut += A_LoopField29 + " " + culyOpenFix + "\n";
                skipNext = 2;
            }
            if (skipNext == 0) {
                resultOut += A_LoopField29 + "\n";
            }
        }
        result = StringTrimRight(resultOut, 1);
        std::vector<std::string> lookIntoFurture2;
        std::vector<std::string> items30 = LoopParseFunc(result, "\n", "\r");
        for (size_t A_Index30 = 0; A_Index30 < items30.size() + 0; A_Index30++) {
            std::string A_LoopField30 = items30[A_Index30 - 0];
            lookIntoFurture2.push_back(Trim(A_LoopField30));
        }
        lookIntoFurture2.push_back(" ");
        resultOut = "";
        skipNext = 0;
        std::string addSpacesAtTheBegginig;
        std::vector<std::string> items31 = LoopParseFunc(result, "\n", "\r");
        for (size_t A_Index31 = 0; A_Index31 < items31.size() + 0; A_Index31++) {
            std::string A_LoopField31 = items31[A_Index31 - 0];
            skipNext--;
            if (skipNext <= 0) {
                skipNext = 0;
            }
            if (langToConvertTo != "lua" && langToConvertTo != "rb" && langToConvertTo != langFileExtension_2) {
                if (Trim(A_LoopField31) == "}" && Trim(lookIntoFurture2[A_Index31 + 1]) == "else {") {
                    skipNext = 2;
                    addSpacesAtTheBegginig = "";
                    std::vector<std::string> items32 = LoopParseFunc(A_LoopField31);
                    for (size_t A_Index32 = 0; A_Index32 < items32.size() + 0; A_Index32++) {
                        std::string A_LoopField32 = items32[A_Index32 - 0];
                        if (A_LoopField32 == " ") {
                            if (A_LoopField32 != " ") {
                                break;
                            }
                            addSpacesAtTheBegginig += StrReplace(A_LoopField32, "}", culyCloseFix);
                        }
                    }
                    resultOut += addSpacesAtTheBegginig + culyCloseFix + " else " + culyOpenFix + "\n";
                }
            }
            if (skipNext == 0) {
                resultOut += A_LoopField31 + "\n";
            }
        }
        result = StringTrimRight(resultOut, 1);
    }
    resultOut = "";
    std::string ALoopField;
    std::vector<std::string> items33 = LoopParseFunc(result, "\n", "\r");
    for (size_t A_Index33 = 0; A_Index33 < items33.size() + 0; A_Index33++) {
        std::string A_LoopField33 = items33[A_Index33 - 0];
        if (CheckOddLeadingSpaces(A_LoopField33) == "1") {
            ALoopField = StringTrimLeft(A_LoopField33, 1);
            resultOut += ALoopField + "\n";
        } else {
            resultOut += A_LoopField33 + "\n";
        }
    }
    result = StringTrimRight(resultOut, 1);
    std::string fixResultFIX = "";
    if (langToConvertTo == langFileExtension_2 && modeCurlyBracesOn == 1) {
        std::vector<std::string> items34 = LoopParseFunc(result, "\n", "\r");
        for (size_t A_Index34 = 0; A_Index34 < items34.size() + 0; A_Index34++) {
            std::string A_LoopField34 = items34[A_Index34 - 0];
            if (Trim(A_LoopField34) == "}") {
                fixResultFIX += StrReplace(A_LoopField34, "}", culyCloseFix) + "\n";
            } else {
                fixResultFIX += A_LoopField34 + "\n";
            }
        }
        result = StringTrimRight(fixResultFIX, 1);
    }
    // Return the result
    return result;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
// path.path.path:propName1[str],propName2[bool],propName3[str array]|path.path.path:propName1[str],propName2[bool],propName3[str array]
std::string OSPstrArrayStrALLobjInOSP = "";
std::string HoldOSPdethodNamePath = "";
std::string findTypeOfOSPprop(std::string fullARRAYstr, std::string FromPath) {
    std::string outType = "";
    // if the fullARRAYstr is in this format
    // path.path.path:propName1[str],propName2[bool],propName3[str array]|path.path.path:propName1[str],propName2[bool],propName3[str array]
    std::string outFormat = "";
    std::string outFormatHELP1 = "";
    std::string outFormatHELP2 = "";
    std::vector<std::string> items35 = LoopParseFunc(fullARRAYstr, "|");
    for (size_t A_Index35 = 0; A_Index35 < items35.size() + 0; A_Index35++) {
        std::string A_LoopField35 = items35[A_Index35 - 0];
        if (Trim(A_LoopField35) != "") {
            outFormatHELP1 = StrSplit(A_LoopField35, ":", 1);
            outFormatHELP2 = StrSplit(A_LoopField35, ":", 2);
            std::vector<std::string> items36 = LoopParseFunc(outFormatHELP2, ",");
            for (size_t A_Index36 = 0; A_Index36 < items36.size() + 0; A_Index36++) {
                std::string A_LoopField36 = items36[A_Index36 - 0];
                outFormat += outFormatHELP1 + "." + A_LoopField36 + "|";
            }
        }
    }
    outFormat = StringTrimRight(outFormat, 1);
    std::vector<std::string> items37 = LoopParseFunc(outFormat, "|");
    for (size_t A_Index37 = 0; A_Index37 < items37.size() + 0; A_Index37++) {
        std::string A_LoopField37 = items37[A_Index37 - 0];
        if (Trim(A_LoopField37) != "") {
            if (StrSplit(Trim(A_LoopField37), "[", 1) == Trim(FromPath)) {
                outType = StrSplit(Trim(A_LoopField37), "[", 2);
                outType = StringTrimRight(outType, 1);
                break;
            }
        }
    }
    if (outType == "vector<int>") {
        outType = "std::vector<int>&";
    }
    else if (outType == "vector<string>") {
        outType = "std::vector<std::string>&";
    }
    else if (outType == "vector<string>") {
        outType = "std::vector<std::string>&";
    }
    else if (outType == "vector<float>") {
        outType = "std::vector<float>&";
    }
    else if (outType == "vector<bool>") {
        outType = "std::vector<bool>&";
    }
    else if (outType == Trim(keyWordINT)) {
        outType = "int";
    }
    else if (outType == Trim(keyWordSTR)) {
        outType = "std::string";
    }
    else if (outType == Trim(keyWordFLOAT)) {
        outType = "float";
    }
    else if (outType == Trim(keyWordBOOL)) {
        outType = "bool";
    }
    else if (outType == Trim(keyWordINT8)) {
        outType = "int8_t";
    }
    else if (outType == Trim(keyWordINT16)) {
        outType = "int16_t";
    }
    else if (outType == Trim(keyWordINT32)) {
        outType = "int32_t";
    }
    else if (outType == Trim(keyWordINT64)) {
        outType = "int64_t";
    }
    return outType;
}
std::string REMOVELastSTRfromDOT(std::string THESTR) {
    std::string THESTRout = "";
    if (Trim(THESTR) == "") {
        return "";
    }
    int count12345 = 0;
    std::vector<std::string> items38 = LoopParseFunc(THESTR, ".");
    for (size_t A_Index38 = 0; A_Index38 < items38.size() + 0; A_Index38++) {
        std::string A_LoopField38 = items38[A_Index38 - 0];
        count12345++;
    }
    std::vector<std::string> items39 = LoopParseFunc(THESTR, ".");
    for (size_t A_Index39 = 0; A_Index39 < items39.size() + 0; A_Index39++) {
        std::string A_LoopField39 = items39[A_Index39 - 0];
        if (count12345 == A_Index39) {
            break;
        } else {
            THESTRout += Trim(A_LoopField39) + ".";
        }
    }
    THESTRout = StringTrimRight(THESTRout, 1);
    return THESTRout;
}
//;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;
std::string replaceTheOSPpathsPY_JS(std::string theSTR123, std::string ALoopFieldIN) {
    if (Trim(theSTR123) == "") {
        return "";
    }
    if (Trim(ALoopFieldIN) == "") {
        return "";
    }
    std::string type = "";
    std::string theSTR123out = "";
    std::string ALoopField = "";
    std::string ALoopField1 = "";
    std::string ALoopField11 = "";
    if (InStr(ALoopFieldIN, "[")) {
        // ALoopFieldIN
        // animalsKingdom.animals.Dog.typeOf2[2]
        ALoopField = StrSplit(Trim(ALoopFieldIN), "[", 1);
        ALoopField1 = StrSplit(Trim(ALoopFieldIN), "[", 1);
        ALoopField11 = StrSplit(Trim(ALoopFieldIN), "[", 2);
        ALoopField1 = REMOVELastSTRfromDOT(ALoopField1) + "[" + ALoopField11;
        // REMOVELastSTRfromDOT(param1)
        theSTR123 = StrReplace(theSTR123, Trim(ALoopField), "OSPHTVMOSP_" + StrReplace(ALoopField1, ".", "_"));
    } else {
        ALoopField = StrSplit(Trim(ALoopFieldIN), "[", 1);
        ALoopField1 = StrSplit(Trim(ALoopFieldIN), "[", 2);
        ALoopField1 = REMOVELastSTRfromDOT(StrSplit(Trim(ALoopFieldIN), "]", 1));
        ALoopField1 = "[" + Trim(StrSplit(ALoopField1, "[", 2)) + "]";
        theSTR123 = StrReplace(theSTR123, Trim(ALoopFieldIN), "OSPHTVMOSP_" + StrReplace(ALoopFieldIN, ".", "_"));
    }
    //this__OSP__this
    theSTR123 = RegExReplace(theSTR123, "\\bthis\\b", "this__OSP__this[0]");
    theSTR123 = StrReplace(theSTR123, "OSPHTVMOSP_OSPHTVMOSP_", "OSPHTVMOSP_");
    return theSTR123;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
std::string replaceTheOSPpathsLEFT(std::string theSTR123, std::string ALoopFieldIN) {
    if (Trim(theSTR123) == "") {
        return "";
    }
    if (Trim(ALoopFieldIN) == "") {
        return "";
    }
    std::string type = "";
    std::string theSTR123out = "";
    std::string ALoopField = "";
    std::string ALoopField1 = "";
    std::string ALoopField11 = "";
    if (InStr(ALoopFieldIN, "[")) {
        // ALoopFieldIN
        // animalsKingdom.animals.Dog.typeOf2[2]
        ALoopField = StrSplit(Trim(ALoopFieldIN), "[", 1);
        ALoopField1 = StrSplit(Trim(ALoopFieldIN), "[", 1);
        ALoopField11 = StrSplit(Trim(ALoopFieldIN), "[", 2);
        ALoopField1 = REMOVELastSTRfromDOT(ALoopField1) + "[" + ALoopField11;
        // REMOVELastSTRfromDOT(param1)
        theSTR123 = StrReplace(theSTR123, Trim(ALoopField), "OSPHTVMOSP_" + StrReplace(ALoopField1, ".", "_"));
    } else {
        ALoopField = StrSplit(Trim(ALoopFieldIN), "[", 1);
        ALoopField1 = StrSplit(Trim(ALoopFieldIN), "[", 2);
        ALoopField1 = REMOVELastSTRfromDOT(StrSplit(Trim(ALoopFieldIN), "]", 1));
        ALoopField1 = "[" + Trim(StrSplit(ALoopField1, "[", 2)) + "]";
        theSTR123 = StrReplace(theSTR123, Trim(ALoopFieldIN), "OSPHTVMOSP_" + StrReplace(ALoopFieldIN, ".", "_"));
    }
    //this__OSP__this
    theSTR123 = RegExReplace(theSTR123, "\\bthis\\b", "std::any_cast<std::string>((*this__OSP__this)[0])");
    theSTR123 = StrReplace(theSTR123, "OSPHTVMOSP_OSPHTVMOSP_", "OSPHTVMOSP_");
    return theSTR123;
}
std::string replaceTheOSPpathsRIGHT(std::string theSTR123, std::string ALoopFieldIN) {
    if (Trim(theSTR123) == "") {
        return "";
    }
    if (Trim(ALoopFieldIN) == "") {
        return "";
    }
    std::string type = "";
    std::string theSTR123out = "";
    std::string ALoopField = "";
    std::string ALoopField1 = "";
    std::string ALoopField11 = "";
    if (InStr(ALoopFieldIN, "[")) {
        // ALoopFieldIN
        // animalsKingdom.animals.Dog.typeOf2[2]
        ALoopField = StrSplit(Trim(ALoopFieldIN), "[", 1);
        ALoopField1 = StrSplit(Trim(ALoopFieldIN), "[", 1);
        ALoopField11 = StrSplit(Trim(ALoopFieldIN), "[", 2);
        ALoopField1 = REMOVELastSTRfromDOT(ALoopField1) + "[" + ALoopField11;
        // REMOVELastSTRfromDOT(param1)
        type = findTypeOfOSPprop(OSPstrArrayStrALLobjInOSP, ALoopField);
        //MsgBox, % type
        theSTR123 = StrReplace(theSTR123, Trim(ALoopField), "std::any_cast<" + type + ">(OSPHTVMOSP_" + StrReplace(ALoopField1, ".", "_") + ")");
    } else {
        ALoopField = StrSplit(Trim(ALoopFieldIN), "[", 1);
        ALoopField1 = StrSplit(Trim(ALoopFieldIN), "[", 2);
        ALoopField1 = REMOVELastSTRfromDOT(StrSplit(Trim(ALoopFieldIN), "]", 1));
        ALoopField1 = "[" + Trim(StrSplit(ALoopField1, "[", 2)) + "]";
        theSTR123 = StrReplace(theSTR123, Trim(ALoopFieldIN), "OSPHTVMOSP_" + StrReplace(ALoopFieldIN, ".", "_"));
    }
    //this__OSP__this
    theSTR123 = RegExReplace(theSTR123, "\\bthis\\b", "std::any_cast<std::string>((*this__OSP__this)[0])");
    theSTR123 = StrReplace(theSTR123, "OSPHTVMOSP_OSPHTVMOSP_", "OSPHTVMOSP_");
    return theSTR123;
}
std::string CheckStringPosition(std::string text, std::string target, std::string reference) {
    std::string posReference = SubStr(text, 1, StrLen(reference));
    std::string posTarget = SubStr(text, 1, StrLen(target));
    // Check if both strings are found (not using InStr)
    if (posReference != "" && posTarget != "") {
        // Manually find the positions of the target and reference
        posTarget = RegExMatch(text, target);
        posReference = RegExMatch(text, reference);
        // Compare positions of target and reference
        if (posTarget < posReference) {
            return "left";
        }
        else if (posTarget > posReference) {
            return "not left";
        } else {
            return "uuh";
        }
    } else {
        return "One or both strings not found.";
    }
    return "huh";
}
std::string getIndexOfTheStrArrayStrOST(std::string ALoopField, std::string theSringOSPlineARRAYstrstrSTR) {
    std::vector<std::string> items40 = LoopParseFunc(theSringOSPlineARRAYstrstrSTR, "|");
    for (size_t A_Index40 = 0; A_Index40 < items40.size() + 0; A_Index40++) {
        std::string A_LoopField40 = items40[A_Index40 - 0];
        if (Trim(StrSplit(A_LoopField40, ":", 1)) == Trim(ALoopField)) {
            return STR(A_Index40);
        }
    }
    return "0";
}
std::string parserOSPgloabl(std::string theSringOSPline, std::string str123) {
    std::string str_1 = "";
    std::string str_2 = "";
    std::string str_3 = "";
    std::string str_4 = "";
    std::string str_5 = "";
    std::string str_6 = "";
    std::string HELPHoldOSPdethodNamePath = "";
    std::vector<std::string> items41 = LoopParseFunc(theSringOSPline, "|");
    for (size_t A_Index41 = 0; A_Index41 < items41.size() + 0; A_Index41++) {
        std::string A_LoopField41 = items41[A_Index41 - 0];
        str_1 += Trim(StrSplit(A_LoopField41, ":", 1)) + "\n";
        str_5 = Trim(StrSplit(A_LoopField41, ":", 1));
        str_6 = Trim(StrSplit(A_LoopField41, ":", 2));
        std::vector<std::string> items42 = LoopParseFunc(str_6, ",");
        for (size_t A_Index42 = 0; A_Index42 < items42.size() + 0; A_Index42++) {
            std::string A_LoopField42 = items42[A_Index42 - 0];
            str_1 += str_5 + "." + Trim(StrSplit(A_LoopField42, "[", 1)) + "[" + STR(A_Index42) + "]\n";
        }
    }
    str_1 += StrReplace(HELPHoldOSPdethodNamePath, "|", "\n");
    std::string shortestLine = "";
    std::string currentLine = "";
    int currentLength = 0;
    int minLength = 0;
    std::string tempStr = "";
    // Sorting by repeatedly finding and appending the shortest line
    for (int A_Index43 = 0; ; A_Index43++) {
        // Initialize variables to track the shortest line in this pass
        shortestLine = "";
        minLength = 999999;
        // Find the shortest line in str_1
        std::vector<std::string> items44 = LoopParseFunc(str_1, "\n", "\r");
        for (size_t A_Index44 = 0; A_Index44 < items44.size() + 0; A_Index44++) {
            std::string A_LoopField44 = items44[A_Index44 - 0];
            currentLine = A_LoopField44;
            currentLength = StrLen(currentLine);
            if (currentLength < minLength) {
                minLength = currentLength;
                shortestLine = currentLine;
            }
        }
        // If no shortest line is found, break (str_1 is empty)
        if (shortestLine == "") {
            break;
        }
        // Add the shortest line to the sorted result
        str_2 += shortestLine + "\n";
        // Rebuild str_1 without the shortest line
        tempStr = "";
        std::vector<std::string> items45 = LoopParseFunc(str_1, "\n", "\r");
        for (size_t A_Index45 = 0; A_Index45 < items45.size() + 0; A_Index45++) {
            std::string A_LoopField45 = items45[A_Index45 - 0];
            if (A_LoopField45 != shortestLine) {
                tempStr += A_LoopField45 + "\n";
            }
        }
        tempStr = StringTrimRight(tempStr, 1);
        str_1 = tempStr;
    }
    // Trim the final trailing newline from str_2
    str_2 = StringTrimRight(str_2, 1);
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    // Initialize an empty result for the reversed lines
    std::string reversedStr = "";
    // Count the number of lines
    int lineCount = 0;
    int index = 0;
    int lineNum = 0;
    std::vector<std::string> items46 = LoopParseFunc(str_2, "\n", "\r");
    for (size_t A_Index46 = 0; A_Index46 < items46.size() + 0; A_Index46++) {
        std::string A_LoopField46 = items46[A_Index46 - 0];
        lineCount++;
    }
    // Reverse the order by re-parsing and appending lines in reverse order
    for (int A_Index47 = 0; A_Index47 < lineCount + 0; A_Index47++) {
        // Inner loop to find the (lineCount - A_Index47 + 1)-th line
        index = lineCount - A_Index47 + 1;
        currentLine = "";
        lineNum = 0;
        std::vector<std::string> items48 = LoopParseFunc(str_2, "\n", "\r");
        for (size_t A_Index48 = 0; A_Index48 < items48.size() + 0; A_Index48++) {
            std::string A_LoopField48 = items48[A_Index48 - 0];
            lineNum++;
            if (lineNum == index) {
                currentLine = A_LoopField48;
                break;
            }
        }
        // Append the line in reverse order
        reversedStr += currentLine + "\n";
    }
    // Trim the final trailing newline
    str_2 = StringTrimRight(reversedStr, 1);
    // Display the sorted result
    //MsgBox, % str_2
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //CheckStringPosition(text, target, reference)
    std::string ALoopField = "";
    std::string ALoopField1 = "";
    std::vector<std::string> items49 = LoopParseFunc(str_2, "\n", "\r");
    for (size_t A_Index49 = 0; A_Index49 < items49.size() + 0; A_Index49++) {
        std::string A_LoopField49 = items49[A_Index49 - 0];
        if (SubStr(A_LoopField49, 1, StrLen(keyWordFunc)) != keyWordFunc) {
            if (langToConvertTo == "cpp") {
                if (Trim(A_LoopField49) != "") {
                    if (InStr(str123, " += ")) {
                        str6 = " += ";
                        str1 = "";
                        str2 = "";
                        str3 = "";
                        str4 = "";
                        str5 = "";
                        str1 = Trim(StrSplit(str123, str6, 1));
                        str2 = Trim(StrSplit(str123, str6, 2));
                        str3 = Trim(replaceTheOSPpathsLEFT(str1, A_LoopField49));
                        str4 = Trim(replaceTheOSPpathsRIGHT(str2, A_LoopField49));
                        str5 = str3 + str6 + str4;
                        str123 = Trim(str5);
                    }
                    else if (InStr(str123, " = ")) {
                        str6 = " = ";
                        str1 = "";
                        str2 = "";
                        str3 = "";
                        str4 = "";
                        str5 = "";
                        str1 = Trim(StrSplit(str123, str6, 1));
                        str2 = Trim(StrSplit(str123, str6, 2));
                        str3 = Trim(replaceTheOSPpathsLEFT(str1, A_LoopField49));
                        str4 = Trim(replaceTheOSPpathsRIGHT(str2, A_LoopField49));
                        str5 = str3 + str6 + str4;
                        str123 = Trim(str5);
                    }
                    else if (InStr(str123, " -= ")) {
                        str6 = " -= ";
                        str1 = "";
                        str2 = "";
                        str3 = "";
                        str4 = "";
                        str5 = "";
                        str1 = Trim(StrSplit(str123, str6, 1));
                        str2 = Trim(StrSplit(str123, str6, 2));
                        str3 = Trim(replaceTheOSPpathsLEFT(str1, A_LoopField49));
                        str4 = Trim(replaceTheOSPpathsRIGHT(str2, A_LoopField49));
                        str5 = str3 + str6 + str4;
                        str123 = Trim(str5);
                    }
                    else if (InStr(str123, " *= ")) {
                        str6 = " *= ";
                        str1 = "";
                        str2 = "";
                        str3 = "";
                        str4 = "";
                        str5 = "";
                        str1 = Trim(StrSplit(str123, str6, 1));
                        str2 = Trim(StrSplit(str123, str6, 2));
                        str3 = Trim(replaceTheOSPpathsLEFT(str1, A_LoopField49));
                        str4 = Trim(replaceTheOSPpathsRIGHT(str2, A_LoopField49));
                        str5 = str3 + str6 + str4;
                        str123 = Trim(str5);
                    }
                    else if (InStr(str123, " /= ")) {
                        str6 = " /= ";
                        str1 = "";
                        str2 = "";
                        str3 = "";
                        str4 = "";
                        str5 = "";
                        str1 = Trim(StrSplit(str123, str6, 1));
                        str2 = Trim(StrSplit(str123, str6, 2));
                        str3 = Trim(replaceTheOSPpathsLEFT(str1, A_LoopField49));
                        str4 = Trim(replaceTheOSPpathsRIGHT(str2, A_LoopField49));
                        str5 = str3 + str6 + str4;
                        str123 = Trim(str5);
                    } else {
                        str123 = replaceTheOSPpathsRIGHT(str123, A_LoopField49);
                    }
                    //;;;;
                }
            } else {
                if (Trim(A_LoopField49) != "") {
                    str123 = replaceTheOSPpathsPY_JS(str123, A_LoopField49);
                }
            }
        }
    }
    return str123;
}
bool isLineAconstruct(std::string line) {
    if (SubStr(StrLower(Trim(line)), 1, StrLen(StrLower(keyWordIF))) == StrLower(keyWordIF)) {
        return true;
    }
    else if (SubStr(StrLower(Trim(line)), 1, StrLen(StrLower(keyWordElseIf))) == StrLower(keyWordElseIf)) {
        return true;
    }
    else if (StrLower(Trim(line)) == StrLower(keyWordElse) || StrLower(Trim(line)) == StrLower(keyWordElse + ":")) {
        return true;
    }
    else if (SubStr(Trim(line), 1, StrLen(keyWordCurlyBraceClose + " " + StrLower(keyWordElse))) == keyWordCurlyBraceClose + " " + StrLower(keyWordElse)) {
        return true;
    }
    else if (SubStr(Trim(line), 1, StrLen(StrLower(keyWordElse) + " " + keyWordCurlyBraceOpen)) == StrLower(keyWordElse) + " " + keyWordCurlyBraceOpen) {
        return true;
    }
    else if (SubStr(StrLower(Trim(line)), 1, StrLen(StrLower(keyWordWhileLoop))) == StrLower(keyWordWhileLoop)) {
        return true;
    }
    else if (StrLower(Trim(line)) == StrLower(keyWordLoopInfinite) || StrLower(Trim(line)) == StrLower(keyWordLoopInfinite + ":")) {
        return true;
    }
    else if (SubStr(Trim(line), 1, StrLen(keyWordCurlyBraceClose + " " + StrLower(keyWordLoopInfinite))) == keyWordCurlyBraceClose + " " + StrLower(keyWordLoopInfinite)) {
        return true;
    }
    else if (SubStr(Trim(line), 1, StrLen(StrLower(keyWordLoopInfinite) + " " + keyWordCurlyBraceOpen)) == StrLower(keyWordLoopInfinite) + " " + keyWordCurlyBraceOpen) {
        return true;
    }
    else if (SubStr(StrLower(Trim(line)), 1, StrLen(StrLower(keyWordLoop))) == StrLower(keyWordLoop)) {
        return true;
    }
    else if (SubStr(StrLower(Trim(line)), 1, StrLen(StrLower(keyWordLoopParse))) == StrLower(keyWordLoopParse)) {
        return true;
    }
    else if (StrLower(Trim(line)) == StrLower(keyWordTry) || StrLower(Trim(line)) == StrLower(keyWordTry + ":")) {
        return true;
    }
    else if (SubStr(Trim(line), 1, StrLen(keyWordCurlyBraceClose + " " + StrLower(keyWordTry))) == keyWordCurlyBraceClose + " " + StrLower(keyWordTry)) {
        return true;
    }
    else if (SubStr(Trim(line), 1, StrLen(StrLower(keyWordTry) + " " + keyWordCurlyBraceOpen)) == StrLower(keyWordTry) + " " + keyWordCurlyBraceOpen) {
        return true;
    }
    else if (SubStr(StrLower(Trim(line)), 1, StrLen(StrLower(keyWordAlliance))) == StrLower(keyWordAlliance)) {
        return true;
    }
    else if (SubStr(StrLower(Trim(line)), 1, StrLen(StrLower(keyWordCrew))) == StrLower(keyWordCrew)) {
        return true;
    }
    else if (SubStr(StrLower(Trim(line)), 1, StrLen(StrLower(keyWordDefObj))) == StrLower(keyWordDefObj)) {
        return true;
    }
    else if (SubStr(StrLower(Trim(line)), 1, StrLen(StrLower(keyWordMethod))) == StrLower(keyWordMethod)) {
        return true;
    }
    else if (SubStr(StrLower(Trim(line)), 1, StrLen(StrLower(keyWordCatch))) == StrLower(keyWordCatch)) {
        return true;
    }
    else if (StrLower(Trim(line)) == StrLower(keyWordFinally) || StrLower(Trim(line)) == StrLower(keyWordFinally + ":")) {
        return true;
    }
    else if (SubStr(Trim(line), 1, StrLen(keyWordCurlyBraceClose + " " + StrLower(keyWordFinally))) == keyWordCurlyBraceClose + " " + StrLower(keyWordFinally)) {
        return true;
    }
    else if (SubStr(Trim(line), 1, StrLen(StrLower(keyWordFinally) + " " + keyWordCurlyBraceOpen)) == StrLower(keyWordFinally) + " " + keyWordCurlyBraceOpen) {
        return true;
    }
    else if (SubStr(StrLower(Trim(line)), 1, StrLen(StrLower(keyWordFunc))) == StrLower(keyWordFunc)) {
        return true;
    }
    return false;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
std::string fixDoubleQuotes(std::string line, int isLast) {
    std::string out = "";
    if (isLast == 0) {
        out = StrReplace(line, Chr(92) + Chr(92) + Chr(34), Chr(92) + Chr(34));
    } else {
        line = StringTrimRight(line, 1);
        out = StrReplace(line, Chr(92) + Chr(92) + Chr(34), Chr(92) + Chr(34)) + Chr(34);
    }
    return out;
}
std::string fixArray1234(std::string line) {
    std::string out = "";
    int started = 0;
    std::vector<std::string> items50 = LoopParseFunc(line);
    for (size_t A_Index50 = 0; A_Index50 < items50.size() + 0; A_Index50++) {
        std::string A_LoopField50 = items50[A_Index50 - 0];
        if (started == 1) {
            if (StrLen(line) == A_Index50 + 1) {
                return out;
            }
            out += A_LoopField50;
        }
        if (A_LoopField50 == "(") {
            started = 1;
        }
    }
    return out;
}
std::string fixArray123(std::string line, std::string arrayMethodStr, int mode) {
    // mode 1 = Append
    // mode 2 = Pop
    // mode 3 = Size
    // mode 4 = Insert
    // mode 5 = Remove
    // mode 6 = IndexOf
    // HTVM_Append
    // HTVM_Pop
    // HTVM_Size
    // HTVM_Insert
    // HTVM_Remove
    // HTVM_IndexOf
    if (langToConvertTo != "swift") {
        if (mode == 1) {
            return "HTVM_Append(" + StrSplit(line, ".", 1) + ", " + fixArray1234(line) + ")";
        }
        if (mode == 2) {
            return "HTVM_Pop(" + StrSplit(line, ".", 1) + ")";
        }
        if (mode == 3) {
            return "HTVM_Size(" + StrSplit(line, ".", 1) + ")";
        }
        if (mode == 4) {
            return "HTVM_Insert(" + StrSplit(line, ".", 1) + ", " + fixArray1234(line) + ")";
        }
        if (mode == 5) {
            return "HTVM_Remove(" + StrSplit(line, ".", 1) + ", " + fixArray1234(line) + ")";
        }
        if (mode == 6) {
            return "HTVM_IndexOf(" + StrSplit(line, ".", 1) + ", " + fixArray1234(line) + ")";
        }
    } else {
        if (mode == 1) {
            return "HTVM_Append(&" + StrSplit(line, ".", 1) + ", " + fixArray1234(line) + ")";
        }
        if (mode == 2) {
            return "HTVM_Pop(&" + StrSplit(line, ".", 1) + ")";
        }
        if (mode == 3) {
            return "HTVM_Size(" + StrSplit(line, ".", 1) + ")";
        }
        if (mode == 4) {
            return "HTVM_Insert(&" + StrSplit(line, ".", 1) + ", " + fixArray1234(line) + ")";
        }
        if (mode == 5) {
            return "HTVM_Remove(&" + StrSplit(line, ".", 1) + ", " + fixArray1234(line) + ")";
        }
        if (mode == 6) {
            return "HTVM_IndexOf(" + StrSplit(line, ".", 1) + ", " + fixArray1234(line) + ")";
        }
    }
    return line;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
std::string arrayParserTranspiler1(std::string line, std::string arrayMethodStr, int mode) {
    if (InStr(line, arrayMethodStr) == false) {
        return line;
    }
    std::string out = "";
    std::string allDelimiters = " ()[],;:'!&|=<>+-*/^%~" + Chr(34) + Chr(9) + Chr(11);
    std::vector<std::string> arrAll;
    std::vector<std::string> items51 = LoopParseFunc(line);
    for (size_t A_Index51 = 0; A_Index51 < items51.size() + 0; A_Index51++) {
        std::string A_LoopField51 = items51[A_Index51 - 0];
        arrAll.push_back(A_LoopField51);
    }
    int i1 = 0;
    std::string tempHold = "";
    int holdPos = 0;
    std::vector<int> holdPositions;
    for (int A_Index52 = 0; A_Index52 < arrAll.size() + 0; A_Index52++) {
        tempHold = "";
        if (arrAll.size() - StrLen(arrayMethodStr) + 1 == i1) {
            break;
        }
        for (int A_Index53 = 0; A_Index53 < StrLen(arrayMethodStr) + 0; A_Index53++) {
            tempHold += arrAll[A_Index53 + i1];
        }
        i1++;
        //print(tempHold)
        if (tempHold == arrayMethodStr) {
            holdPos = i1;
            //print(holdPos)
            holdPositions.push_back(holdPos);
        }
    }
    //print("===========================================")
    int holdPositionsTEMP = 0;
    for (int A_Index54 = 0; A_Index54 < holdPositions.size() + 0; A_Index54++) {
        holdPositionsTEMP = holdPositions[A_Index54];
        i1 = arrAll.size();
        tempHold = "";
        for (int A_Index55 = 0; A_Index55 < arrAll.size() + 0; A_Index55++) {
            if (holdPositionsTEMP >= i1 + 1) {
                if (InStr(allDelimiters, arrAll[i1]) == false) {
                    tempHold += arrAll[i1 - 1];
                } else {
                    break;
                }
            }
            i1--;
        }
        //print(await StrLen(Trim(RegExReplace(tempHold, "[^A-Za-z0-9_]", ""))))
        holdPositions[A_Index54] = holdPositions[A_Index54] - StrLen(Trim(RegExReplace(tempHold, "[^A-Za-z0-9_]", "")));
    }
    //;;;;;;;;;;;;;;;;;;
    int foundFirstParenthesis = 0;
    int ParenthesisStackOPEN = 0;
    int ParenthesisStackCLOSE = 0;
    std::vector<int> holdPositionsEnd;
    holdPositionsTEMP = 0;
    for (int A_Index56 = 0; A_Index56 < holdPositions.size() + 0; A_Index56++) {
        holdPositionsTEMP = holdPositions[A_Index56];
        i1 = 0;
        tempHold = "";
        foundFirstParenthesis = 0;
        ParenthesisStackOPEN = 0;
        ParenthesisStackCLOSE = 0;
        for (int A_Index57 = 0; A_Index57 < arrAll.size() + 0; A_Index57++) {
            if (holdPositionsTEMP < i1 + 1) {
                if (arrAll[i1] == "(") {
                    foundFirstParenthesis = 1;
                }
                if (arrAll[i1] == "(" && foundFirstParenthesis == 1) {
                    ParenthesisStackOPEN++;
                }
                if (arrAll[i1] == ")" && foundFirstParenthesis == 1) {
                    ParenthesisStackCLOSE++;
                }
                tempHold += arrAll[i1 - 1];
                if (ParenthesisStackOPEN == ParenthesisStackCLOSE && foundFirstParenthesis == 1) {
                    tempHold += arrAll[i1];
                    holdPositionsEnd.push_back(i1 + 1);
                    break;
                }
            }
            i1++;
        }
        //print(tempHold)
    }
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    int startPosReplace = 0;
    int endPosReplace = 0;
    int beenInside = 0;
    std::string holdDebug = "";
    int holdDebugLen = 0;
    int canOut = 1;
    for (int A_Index58 = 0; A_Index58 < holdPositions.size() + 0; A_Index58++) {
        startPosReplace = holdPositions[holdPositions.size() - A_Index58 - 1];
        endPosReplace = holdPositionsEnd[holdPositions.size() - A_Index58 - 1];
        holdDebug = "";
        beenInside = 0;
        holdDebugLen = 0;
        canOut = 1;
        std::vector<std::string> items59 = LoopParseFunc(line);
        for (size_t A_Index59 = 0; A_Index59 < items59.size() + 0; A_Index59++) {
            std::string A_LoopField59 = items59[A_Index59 - 0];
            if (A_Index59 + 1 >= startPosReplace && A_Index59 + 1 <= endPosReplace) {
                holdDebug += A_LoopField59;
            }
        }
        holdDebugLen = StrLen(holdDebug);
        std::vector<std::string> items60 = LoopParseFunc(line);
        for (size_t A_Index60 = 0; A_Index60 < items60.size() + 0; A_Index60++) {
            std::string A_LoopField60 = items60[A_Index60 - 0];
            if (A_Index60 + 1 >= startPosReplace && A_Index60 + 1 <= endPosReplace) {
                beenInside++;
            }
            if (beenInside == 1) {
                out += fixArray123(holdDebug, arrayMethodStr, mode);
                canOut = 0;
            } else {
                if (canOut == 0) {
                    holdDebugLen--;
                    if (holdDebugLen == 0) {
                        canOut = 1;
                    }
                }
                if (canOut == 1) {
                    out += A_LoopField60;
                }
            }
        }
        //print("|" . holdDebug . "|")
        line = out;
        out = "";
    }
    return line;
}
std::string arrayParserTranspiler(std::string line) {
    // mode 1 = Append
    // mode 2 = Pop
    // mode 3 = Size
    // mode 4 = Insert
    // mode 5 = Remove
    // mode 6 = IndexOf
    if (langToConvertTo == langFileExtension_2) {
        line = HTVMmatchStrRrplace(line, "." + keyWordArrayAppend + "(", "." + keyWordArrayAppend_2 + "(");
        line = HTVMmatchStrRrplace(line, "." + keyWordArrayPop + "(", "." + keyWordArrayPop_2 + "(");
        line = HTVMmatchStrRrplace(line, "." + keyWordArraySize + "(", "." + keyWordArraySize_2 + "(");
        line = HTVMmatchStrRrplace(line, "." + keyWordArrayInsert + "(", "." + keyWordArrayInsert_2 + "(");
        line = HTVMmatchStrRrplace(line, "." + keyWordArrayRemove + "(", "." + keyWordArrayRemove_2 + "(");
        line = HTVMmatchStrRrplace(line, "." + keyWordArrayIndexOf + "(", "." + keyWordArrayIndexOf_2 + "(");
    } else {
        line = arrayParserTranspiler1(line, keyWordArrayAppend + "(", 1);
        line = arrayParserTranspiler1(line, keyWordArrayPop + "(", 2);
        line = arrayParserTranspiler1(line, keyWordArraySize + "(", 3);
        line = arrayParserTranspiler1(line, keyWordArrayInsert + "(", 4);
        line = arrayParserTranspiler1(line, keyWordArrayRemove + "(", 5);
        line = arrayParserTranspiler1(line, keyWordArrayIndexOf + "(", 6);
    }
    return line;
}
std::string getFuncTypeConvert(std::string type) {
    std::string theType = "";
    type = Trim(type);
    if (langToConvertTo == "cpp") {
        if (type == keyWordVoid) {
            theType = "void";
        }
        if (type == keyWordDouble) {
            theType = "double";
        }
        if (type == keyWordChar) {
            theType = "char";
        }
        if (type == keyWordUint8) {
            theType = "uint8_t";
        }
        if (type == keyWordUint16) {
            theType = "uint16_t";
        }
        if (type == keyWordUint32) {
            theType = "uint32_t";
        }
        if (type == keyWordUint64) {
            theType = "uint64_t";
        }
        if (type == keyWordINT) {
            theType = "int";
        }
        if (type == keyWordSTR) {
            theType = "std::string";
        }
        if (type == keyWordBOOL) {
            theType = "bool";
        }
        if (type == keyWordFLOAT) {
            theType = "float";
        }
        if (type == keyWordINT8) {
            theType = "int8_t";
        }
        if (type == keyWordINT16) {
            theType = "int16_t";
        }
        if (type == keyWordINT32) {
            theType = "int32_t";
        }
        if (type == keyWordINT64) {
            theType = "int64_t";
        }
        if (type == keyWordArrayDefinition) {
            theType = "std::vector<void>";
        }
        if (type == keyWordArrayOfIntegersDefinition) {
            theType = "std::vector<int>";
        }
        if (type == keyWordArrayOfStringsDefinition) {
            theType = "std::vector<std::string>";
        }
        if (type == keyWordArrayOfFloatingPointNumbersDefinition) {
            theType = "std::vector<float>";
        }
        if (type == keyWordArrayOfBooleansDefinition) {
            theType = "std::vector<bool>";
        }
    }
    if (langToConvertTo == "py") {
        theType = "";
    }
    if (langToConvertTo == "js") {
        theType = "";
    }
    if (langToConvertTo == "go") {
        if (type == keyWordVoid) {
            theType = "";
        }
        if (type == keyWordDouble) {
            theType = "float64";
        }
        if (type == keyWordChar) {
            theType = "byte";
        }
        if (type == keyWordUint8) {
            theType = "uint8";
        }
        if (type == keyWordUint16) {
            theType = "uint16";
        }
        if (type == keyWordUint32) {
            theType = "uint32";
        }
        if (type == keyWordUint64) {
            theType = "uint64";
        }
        if (type == keyWordINT) {
            theType = "int";
        }
        if (type == keyWordSTR) {
            theType = "string";
        }
        if (type == keyWordBOOL) {
            theType = "bool";
        }
        if (type == keyWordFLOAT) {
            theType = "float32";
        }
        if (type == keyWordINT8) {
            theType = "int8";
        }
        if (type == keyWordINT16) {
            theType = "int16";
        }
        if (type == keyWordINT32) {
            theType = "int32";
        }
        if (type == keyWordINT64) {
            theType = "int64";
        }
        if (type == keyWordArrayDefinition) {
            theType = "[]string";
        }
        if (type == keyWordArrayOfIntegersDefinition) {
            theType = "[]int";
        }
        if (type == keyWordArrayOfStringsDefinition) {
            theType = "[]string";
        }
        if (type == keyWordArrayOfFloatingPointNumbersDefinition) {
            theType = "[]float32";
        }
        if (type == keyWordArrayOfBooleansDefinition) {
            theType = "[]bool";
        }
    }
    if (langToConvertTo == "lua") {
        theType = "";
    }
    if (langToConvertTo == "cs") {
        if (type == keyWordVoid) {
            theType = "void";
        }
        if (type == keyWordDouble) {
            theType = "double";
        }
        if (type == keyWordChar) {
            theType = "char";
        }
        if (type == keyWordUint8) {
            theType = "byte";
        }
        if (type == keyWordUint16) {
            theType = "ushort";
        }
        if (type == keyWordUint32) {
            theType = "uint";
        }
        if (type == keyWordUint64) {
            theType = "ulong";
        }
        if (type == keyWordINT) {
            theType = "int";
        }
        if (type == keyWordSTR) {
            theType = "string";
        }
        if (type == keyWordBOOL) {
            theType = "bool";
        }
        if (type == keyWordFLOAT) {
            theType = "float";
        }
        if (type == keyWordINT8) {
            theType = "sbyte";
        }
        if (type == keyWordINT16) {
            theType = "short";
        }
        if (type == keyWordINT32) {
            theType = "int";
        }
        if (type == keyWordINT64) {
            theType = "long";
        }
        if (type == keyWordArrayDefinition) {
            theType = "List<string>";
        }
        if (type == keyWordArrayOfIntegersDefinition) {
            theType = "List<int>";
        }
        if (type == keyWordArrayOfStringsDefinition) {
            theType = "List<string>";
        }
        if (type == keyWordArrayOfFloatingPointNumbersDefinition) {
            theType = "List<float>";
        }
        if (type == keyWordArrayOfBooleansDefinition) {
            theType = "List<bool>";
        }
    }
    if (langToConvertTo == "java") {
        if (type == keyWordVoid) {
            theType = "void";
        }
        if (type == keyWordDouble) {
            theType = "double";
        }
        if (type == keyWordChar) {
            theType = "char";
        }
        if (type == keyWordUint8) {
            theType = "byte ";
        }
        if (type == keyWordUint16) {
            theType = "short";
        }
        if (type == keyWordUint32) {
            theType = "int";
        }
        if (type == keyWordUint64) {
            theType = "long";
        }
        if (type == keyWordINT) {
            theType = "int";
        }
        if (type == keyWordSTR) {
            theType = "String";
        }
        if (type == keyWordBOOL) {
            theType = "boolean";
        }
        if (type == keyWordFLOAT) {
            theType = "float";
        }
        if (type == keyWordINT8) {
            theType = "byte";
        }
        if (type == keyWordINT16) {
            theType = "short";
        }
        if (type == keyWordINT32) {
            theType = "int";
        }
        if (type == keyWordINT64) {
            theType = "long";
        }
        if (type == keyWordArrayDefinition) {
            theType = "ArrayList<String>";
        }
        if (type == keyWordArrayOfIntegersDefinition) {
            theType = "ArrayList<Integer>";
        }
        if (type == keyWordArrayOfStringsDefinition) {
            theType = "ArrayList<String>";
        }
        if (type == keyWordArrayOfFloatingPointNumbersDefinition) {
            theType = "ArrayList<Float>";
        }
        if (type == keyWordArrayOfBooleansDefinition) {
            theType = "ArrayList<Boolean>";
        }
    }
    if (langToConvertTo == "kt") {
        if (type == keyWordVoid) {
            theType = "";
        }
        if (type == keyWordDouble) {
            theType = "Double";
        }
        if (type == keyWordChar) {
            theType = "Char";
        }
        if (type == keyWordUint8) {
            theType = "UByte";
        }
        if (type == keyWordUint16) {
            theType = "UShort";
        }
        if (type == keyWordUint32) {
            theType = "UInt";
        }
        if (type == keyWordUint64) {
            theType = "ULong";
        }
        if (type == keyWordINT) {
            theType = "Int";
        }
        if (type == keyWordSTR) {
            theType = "String";
        }
        if (type == keyWordBOOL) {
            theType = "Boolean";
        }
        if (type == keyWordFLOAT) {
            theType = "Float";
        }
        if (type == keyWordINT8) {
            theType = "Byte";
        }
        if (type == keyWordINT16) {
            theType = "Short";
        }
        if (type == keyWordINT32) {
            theType = "Int";
        }
        if (type == keyWordINT64) {
            theType = "Long";
        }
        if (type == keyWordArrayDefinition) {
            theType = "MutableList<String>";
        }
        if (type == keyWordArrayOfIntegersDefinition) {
            theType = "MutableList<Int>";
        }
        if (type == keyWordArrayOfStringsDefinition) {
            theType = "MutableList<String>";
        }
        if (type == keyWordArrayOfFloatingPointNumbersDefinition) {
            theType = "MutableList<Float>";
        }
        if (type == keyWordArrayOfBooleansDefinition) {
            theType = "MutableList<Boolean>";
        }
    }
    if (langToConvertTo == "rb") {
        theType = "";
    }
    if (langToConvertTo == "nim") {
        if (type == keyWordVoid) {
            theType = "";
        }
        if (type == keyWordDouble) {
            theType = "float";
        }
        if (type == keyWordChar) {
            theType = "char";
        }
        if (type == keyWordUint8) {
            theType = "uint8";
        }
        if (type == keyWordUint16) {
            theType = "uint16";
        }
        if (type == keyWordUint32) {
            theType = "uint32";
        }
        if (type == keyWordUint64) {
            theType = "uint64";
        }
        if (type == keyWordINT) {
            theType = "int";
        }
        if (type == keyWordSTR) {
            theType = "string";
        }
        if (type == keyWordBOOL) {
            theType = "bool";
        }
        if (type == keyWordFLOAT) {
            theType = "float";
        }
        if (type == keyWordINT8) {
            theType = "int8";
        }
        if (type == keyWordINT16) {
            theType = "int16";
        }
        if (type == keyWordINT32) {
            theType = "int32";
        }
        if (type == keyWordINT64) {
            theType = "int64";
        }
        if (type == keyWordArrayDefinition) {
            theType = "seq[string]";
        }
        if (type == keyWordArrayOfIntegersDefinition) {
            theType = "seq[int]";
        }
        if (type == keyWordArrayOfStringsDefinition) {
            theType = "seq[string]";
        }
        if (type == keyWordArrayOfFloatingPointNumbersDefinition) {
            theType = "seq[float64]";
        }
        if (type == keyWordArrayOfBooleansDefinition) {
            theType = "seq[bool]";
        }
    }
    if (langToConvertTo == "ahk") {
        theType = "";
    }
    if (langToConvertTo == "swift") {
        if (type == keyWordVoid) {
            theType = "";
        }
        if (type == keyWordDouble) {
            theType = "Double";
        }
        if (type == keyWordChar) {
            theType = "Character";
        }
        if (type == keyWordUint8) {
            theType = "UInt8";
        }
        if (type == keyWordUint16) {
            theType = "UInt16";
        }
        if (type == keyWordUint32) {
            theType = "UInt32";
        }
        if (type == keyWordUint64) {
            theType = "UInt64";
        }
        if (type == keyWordINT) {
            theType = "Int";
        }
        if (type == keyWordSTR) {
            theType = "String";
        }
        if (type == keyWordBOOL) {
            theType = "Bool";
        }
        if (type == keyWordFLOAT) {
            theType = "Float";
        }
        if (type == keyWordINT8) {
            theType = "Int8";
        }
        if (type == keyWordINT16) {
            theType = "Int16";
        }
        if (type == keyWordINT32) {
            theType = "Int32";
        }
        if (type == keyWordINT64) {
            theType = "Int64";
        }
        if (type == keyWordArrayDefinition) {
            theType = "[String]";
        }
        if (type == keyWordArrayOfIntegersDefinition) {
            theType = "[Int]";
        }
        if (type == keyWordArrayOfStringsDefinition) {
            theType = "[String]";
        }
        if (type == keyWordArrayOfFloatingPointNumbersDefinition) {
            theType = "[Float]";
        }
        if (type == keyWordArrayOfBooleansDefinition) {
            theType = "[Bool]";
        }
    }
    if (langToConvertTo == "dart") {
        if (type == keyWordVoid) {
            theType = "void";
        }
        if (type == keyWordDouble) {
            theType = "double";
        }
        if (type == keyWordChar) {
            theType = "String";
        }
        if (type == keyWordUint8) {
            theType = "int";
        }
        if (type == keyWordUint16) {
            theType = "int";
        }
        if (type == keyWordUint32) {
            theType = "int";
        }
        if (type == keyWordUint64) {
            theType = "int";
        }
        if (type == keyWordINT) {
            theType = "int";
        }
        if (type == keyWordSTR) {
            theType = "String";
        }
        if (type == keyWordBOOL) {
            theType = "bool";
        }
        if (type == keyWordFLOAT) {
            theType = "double";
        }
        if (type == keyWordINT8) {
            theType = "int";
        }
        if (type == keyWordINT16) {
            theType = "int";
        }
        if (type == keyWordINT32) {
            theType = "int";
        }
        if (type == keyWordINT64) {
            theType = "int";
        }
        if (type == keyWordArrayDefinition) {
            theType = "List<String>";
        }
        if (type == keyWordArrayOfIntegersDefinition) {
            theType = "List<int>";
        }
        if (type == keyWordArrayOfStringsDefinition) {
            theType = "List<String>";
        }
        if (type == keyWordArrayOfFloatingPointNumbersDefinition) {
            theType = "List<double>";
        }
        if (type == keyWordArrayOfBooleansDefinition) {
            theType = "List<bool>";
        }
    }
    if (langToConvertTo == "ts") {
        if (type == keyWordVoid) {
            theType = "void";
        }
        if (type == keyWordDouble) {
            theType = "number";
        }
        if (type == keyWordChar) {
            theType = "string";
        }
        if (type == keyWordUint8) {
            theType = "number";
        }
        if (type == keyWordUint16) {
            theType = "number";
        }
        if (type == keyWordUint32) {
            theType = "number";
        }
        if (type == keyWordUint64) {
            theType = "bigint";
        }
        if (type == keyWordINT) {
            theType = "number";
        }
        if (type == keyWordSTR) {
            theType = "string";
        }
        if (type == keyWordBOOL) {
            theType = "boolean";
        }
        if (type == keyWordFLOAT) {
            theType = "number";
        }
        if (type == keyWordINT8) {
            theType = "number";
        }
        if (type == keyWordINT16) {
            theType = "number";
        }
        if (type == keyWordINT32) {
            theType = "number";
        }
        if (type == keyWordINT64) {
            theType = "bigint";
        }
        if (type == keyWordArrayDefinition) {
            theType = "string[]";
        }
        if (type == keyWordArrayOfIntegersDefinition) {
            theType = "number[]";
        }
        if (type == keyWordArrayOfStringsDefinition) {
            theType = "string[]";
        }
        if (type == keyWordArrayOfFloatingPointNumbersDefinition) {
            theType = "number[]";
        }
        if (type == keyWordArrayOfBooleansDefinition) {
            theType = "boolean[]";
        }
    }
    if (langToConvertTo == "groovy") {
        theType = "";
    }
    if (langToConvertTo == langFileExtension_2) {
        // keyWordVoid
        // keyWordDouble
        // keyWordChar
        // keyWordUint8
        // keyWordUint16
        // keyWordUint32
        // keyWordUint64
        // keyWordINT
        // keyWordSTR
        // keyWordBOOL
        // keyWordFLOAT
        // keyWordINT8
        // keyWordINT16
        // keyWordINT32
        // keyWordINT64
        // keyWordArrayDefinition
        // keyWordArrayOfIntegersDefinition
        // keyWordArrayOfStringsDefinition
        // keyWordArrayOfFloatingPointNumbersDefinition
        // keyWordArrayOfBooleansDefinition
        if (type == keyWordVoid) {
            theType = keyWordVoid_2;
        }
        if (type == keyWordDouble) {
            theType = keyWordDouble_2;
        }
        if (type == keyWordChar) {
            theType = keyWordChar_2;
        }
        if (type == keyWordUint8) {
            theType = keyWordUint8_2;
        }
        if (type == keyWordUint16) {
            theType = keyWordUint16_2;
        }
        if (type == keyWordUint32) {
            theType = keyWordUint32_2;
        }
        if (type == keyWordUint64) {
            theType = keyWordUint64_2;
        }
        if (type == keyWordINT) {
            theType = keyWordINT_2;
        }
        if (type == keyWordSTR) {
            theType = keyWordSTR_2;
        }
        if (type == keyWordBOOL) {
            theType = keyWordBOOL_2;
        }
        if (type == keyWordFLOAT) {
            theType = keyWordFLOAT_2;
        }
        if (type == keyWordINT8) {
            theType = keyWordINT8_2;
        }
        if (type == keyWordINT16) {
            theType = keyWordINT16_2;
        }
        if (type == keyWordINT32) {
            theType = keyWordINT32_2;
        }
        if (type == keyWordINT64) {
            theType = keyWordINT64_2;
        }
        if (type == keyWordArrayDefinition) {
            theType = keyWordArrayDefinition_2;
        }
        if (type == keyWordArrayOfIntegersDefinition) {
            theType = keyWordArrayOfIntegersDefinition_2;
        }
        if (type == keyWordArrayOfStringsDefinition) {
            theType = keyWordArrayOfStringsDefinition_2;
        }
        if (type == keyWordArrayOfFloatingPointNumbersDefinition) {
            theType = keyWordArrayOfFloatingPointNumbersDefinition_2;
        }
        if (type == keyWordArrayOfBooleansDefinition) {
            theType = keyWordArrayOfBooleansDefinition_2;
        }
    }
    return theType;
}
std::string getTheLastWord(std::string line) {
    if (InStr(Trim(line), " ") == false) {
        return line;
    }
    std::vector<std::string> items61 = LoopParseFunc(line, " ");
    for (size_t A_Index61 = 0; A_Index61 < items61.size() + 0; A_Index61++) {
        std::string A_LoopField61 = items61[A_Index61 - 0];
        line = A_LoopField61;
    }
    return line;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
std::vector<std::string> GETfullLangAllOperators() {
    std::vector<std::string> fullLangAllOperators;
    if (langToConvertTo == "cpp") {
        fullLangAllOperators.push_back("nullptr");
        fullLangAllOperators.push_back("true");
        fullLangAllOperators.push_back("false");
        fullLangAllOperators.push_back("+");
        fullLangAllOperators.push_back("+");
        fullLangAllOperators.push_back("-");
        fullLangAllOperators.push_back("*");
        fullLangAllOperators.push_back("/");
        fullLangAllOperators.push_back("%");
        fullLangAllOperators.push_back("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push_back("==");
        fullLangAllOperators.push_back("==");
        fullLangAllOperators.push_back("!=");
        fullLangAllOperators.push_back(">");
        fullLangAllOperators.push_back("<");
        fullLangAllOperators.push_back(">=");
        fullLangAllOperators.push_back("<=");
        fullLangAllOperators.push_back("&&");
        fullLangAllOperators.push_back("||");
        fullLangAllOperators.push_back("!");
        fullLangAllOperators.push_back("&");
        fullLangAllOperators.push_back("|");
        fullLangAllOperators.push_back("^");
        fullLangAllOperators.push_back("~");
        fullLangAllOperators.push_back("<<");
        fullLangAllOperators.push_back(">>");
        fullLangAllOperators.push_back("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push_back("?");
        fullLangAllOperators.push_back(":");
    }
    if (langToConvertTo == "py") {
        fullLangAllOperators.push_back("None");
        fullLangAllOperators.push_back("True");
        fullLangAllOperators.push_back("False");
        fullLangAllOperators.push_back("+");
        fullLangAllOperators.push_back("+");
        fullLangAllOperators.push_back("-");
        fullLangAllOperators.push_back("*");
        fullLangAllOperators.push_back("/");
        fullLangAllOperators.push_back("%");
        fullLangAllOperators.push_back("**");
        fullLangAllOperators.push_back("==");
        fullLangAllOperators.push_back("is");
        fullLangAllOperators.push_back("!=");
        fullLangAllOperators.push_back(">");
        fullLangAllOperators.push_back("<");
        fullLangAllOperators.push_back(">=");
        fullLangAllOperators.push_back("<=");
        fullLangAllOperators.push_back("and");
        fullLangAllOperators.push_back("or");
        fullLangAllOperators.push_back("not");
        fullLangAllOperators.push_back("&");
        fullLangAllOperators.push_back("|");
        fullLangAllOperators.push_back("^");
        fullLangAllOperators.push_back("~");
        fullLangAllOperators.push_back("<<");
        fullLangAllOperators.push_back(">>");
        fullLangAllOperators.push_back("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push_back("?");
        fullLangAllOperators.push_back(":");
    }
    if (langToConvertTo == "js") {
        fullLangAllOperators.push_back("null");
        fullLangAllOperators.push_back("true");
        fullLangAllOperators.push_back("false");
        fullLangAllOperators.push_back("+");
        fullLangAllOperators.push_back("+");
        fullLangAllOperators.push_back("-");
        fullLangAllOperators.push_back("*");
        fullLangAllOperators.push_back("/");
        fullLangAllOperators.push_back("%");
        fullLangAllOperators.push_back("**");
        if (useJavaScriptAlwaysTripleEqual == "on") {
            fullLangAllOperators.push_back("===");
        } else {
            fullLangAllOperators.push_back("==");
        }
        fullLangAllOperators.push_back("===");
        fullLangAllOperators.push_back("!=");
        fullLangAllOperators.push_back(">");
        fullLangAllOperators.push_back("<");
        fullLangAllOperators.push_back(">=");
        fullLangAllOperators.push_back("<=");
        fullLangAllOperators.push_back("&&");
        fullLangAllOperators.push_back("||");
        fullLangAllOperators.push_back("!");
        fullLangAllOperators.push_back("&");
        fullLangAllOperators.push_back("|");
        fullLangAllOperators.push_back("^");
        fullLangAllOperators.push_back("~");
        fullLangAllOperators.push_back("<<");
        fullLangAllOperators.push_back(">>");
        fullLangAllOperators.push_back(">>>");
        fullLangAllOperators.push_back("?");
        fullLangAllOperators.push_back(":");
    }
    if (langToConvertTo == "go") {
        fullLangAllOperators.push_back("nil");
        fullLangAllOperators.push_back("true");
        fullLangAllOperators.push_back("false");
        fullLangAllOperators.push_back("+");
        fullLangAllOperators.push_back("+");
        fullLangAllOperators.push_back("-");
        fullLangAllOperators.push_back("*");
        fullLangAllOperators.push_back("/");
        fullLangAllOperators.push_back("%");
        fullLangAllOperators.push_back("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push_back("==");
        fullLangAllOperators.push_back("==");
        fullLangAllOperators.push_back("!=");
        fullLangAllOperators.push_back(">");
        fullLangAllOperators.push_back("<");
        fullLangAllOperators.push_back(">=");
        fullLangAllOperators.push_back("<=");
        fullLangAllOperators.push_back("&&");
        fullLangAllOperators.push_back("||");
        fullLangAllOperators.push_back("!");
        fullLangAllOperators.push_back("&");
        fullLangAllOperators.push_back("|");
        fullLangAllOperators.push_back("^");
        fullLangAllOperators.push_back("^");
        fullLangAllOperators.push_back("<<");
        fullLangAllOperators.push_back(">>");
        fullLangAllOperators.push_back("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push_back("THIS OPERATOR DOES NOT EXIST IN GO SINCE GO DOES NOT HAVE A TERNARY OPERATOR");
        fullLangAllOperators.push_back("THIS OPERATOR DOES NOT EXIST IN GO SINCE GO DOES NOT HAVE A TERNARY OPERATOR");
    }
    if (langToConvertTo == "lua") {
        fullLangAllOperators.push_back("nil");
        fullLangAllOperators.push_back("true");
        fullLangAllOperators.push_back("false");
        fullLangAllOperators.push_back("..");
        fullLangAllOperators.push_back("+");
        fullLangAllOperators.push_back("-");
        fullLangAllOperators.push_back("*");
        fullLangAllOperators.push_back("/");
        fullLangAllOperators.push_back("%");
        fullLangAllOperators.push_back("^");
        fullLangAllOperators.push_back("==");
        fullLangAllOperators.push_back("==");
        fullLangAllOperators.push_back("~=");
        fullLangAllOperators.push_back(">");
        fullLangAllOperators.push_back("<");
        fullLangAllOperators.push_back(">=");
        fullLangAllOperators.push_back("<=");
        fullLangAllOperators.push_back("and");
        fullLangAllOperators.push_back("or");
        fullLangAllOperators.push_back("not");
        fullLangAllOperators.push_back("&");
        fullLangAllOperators.push_back("|");
        fullLangAllOperators.push_back("~");
        fullLangAllOperators.push_back("~");
        fullLangAllOperators.push_back("<<");
        fullLangAllOperators.push_back(">>");
        fullLangAllOperators.push_back("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push_back("?");
        fullLangAllOperators.push_back(":");
    }
    if (langToConvertTo == "cs") {
        fullLangAllOperators.push_back("null");
        fullLangAllOperators.push_back("true");
        fullLangAllOperators.push_back("false");
        fullLangAllOperators.push_back("+");
        fullLangAllOperators.push_back("+");
        fullLangAllOperators.push_back("-");
        fullLangAllOperators.push_back("*");
        fullLangAllOperators.push_back("/");
        fullLangAllOperators.push_back("%");
        fullLangAllOperators.push_back("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push_back("==");
        fullLangAllOperators.push_back("==");
        fullLangAllOperators.push_back("!=");
        fullLangAllOperators.push_back(">");
        fullLangAllOperators.push_back("<");
        fullLangAllOperators.push_back(">=");
        fullLangAllOperators.push_back("<=");
        fullLangAllOperators.push_back("&&");
        fullLangAllOperators.push_back("||");
        fullLangAllOperators.push_back("!");
        fullLangAllOperators.push_back("&");
        fullLangAllOperators.push_back("|");
        fullLangAllOperators.push_back("^");
        fullLangAllOperators.push_back("~");
        fullLangAllOperators.push_back("<<");
        fullLangAllOperators.push_back(">>");
        fullLangAllOperators.push_back("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push_back("?");
        fullLangAllOperators.push_back(":");
    }
    if (langToConvertTo == "java") {
        fullLangAllOperators.push_back("null");
        fullLangAllOperators.push_back("true");
        fullLangAllOperators.push_back("false");
        fullLangAllOperators.push_back("+");
        fullLangAllOperators.push_back("+");
        fullLangAllOperators.push_back("-");
        fullLangAllOperators.push_back("*");
        fullLangAllOperators.push_back("/");
        fullLangAllOperators.push_back("%");
        fullLangAllOperators.push_back("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push_back("==");
        fullLangAllOperators.push_back("==");
        fullLangAllOperators.push_back("!=");
        fullLangAllOperators.push_back(">");
        fullLangAllOperators.push_back("<");
        fullLangAllOperators.push_back(">=");
        fullLangAllOperators.push_back("<=");
        fullLangAllOperators.push_back("&&");
        fullLangAllOperators.push_back("||");
        fullLangAllOperators.push_back("!");
        fullLangAllOperators.push_back("&");
        fullLangAllOperators.push_back("|");
        fullLangAllOperators.push_back("^");
        fullLangAllOperators.push_back("~");
        fullLangAllOperators.push_back("<<");
        fullLangAllOperators.push_back(">>");
        fullLangAllOperators.push_back(">>>");
        fullLangAllOperators.push_back("?");
        fullLangAllOperators.push_back(":");
    }
    if (langToConvertTo == "kt") {
        fullLangAllOperators.push_back("null");
        fullLangAllOperators.push_back("true");
        fullLangAllOperators.push_back("false");
        fullLangAllOperators.push_back("+");
        fullLangAllOperators.push_back("+");
        fullLangAllOperators.push_back("-");
        fullLangAllOperators.push_back("*");
        fullLangAllOperators.push_back("/");
        fullLangAllOperators.push_back("%");
        fullLangAllOperators.push_back("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push_back("==");
        fullLangAllOperators.push_back("===");
        fullLangAllOperators.push_back("!=");
        fullLangAllOperators.push_back(">");
        fullLangAllOperators.push_back("<");
        fullLangAllOperators.push_back(">=");
        fullLangAllOperators.push_back("<=");
        fullLangAllOperators.push_back("&&");
        fullLangAllOperators.push_back("||");
        fullLangAllOperators.push_back("!");
        fullLangAllOperators.push_back("and");
        fullLangAllOperators.push_back("or");
        fullLangAllOperators.push_back("xor");
        fullLangAllOperators.push_back("inv");
        fullLangAllOperators.push_back("shl");
        fullLangAllOperators.push_back("shr");
        fullLangAllOperators.push_back("ushr");
        fullLangAllOperators.push_back("?");
        fullLangAllOperators.push_back(":");
    }
    if (langToConvertTo == "rb") {
        fullLangAllOperators.push_back("nil");
        fullLangAllOperators.push_back("true");
        fullLangAllOperators.push_back("false");
        fullLangAllOperators.push_back("+");
        fullLangAllOperators.push_back("+");
        fullLangAllOperators.push_back("-");
        fullLangAllOperators.push_back("*");
        fullLangAllOperators.push_back("/");
        fullLangAllOperators.push_back("%");
        fullLangAllOperators.push_back("**");
        fullLangAllOperators.push_back("==");
        fullLangAllOperators.push_back("==");
        fullLangAllOperators.push_back("!=");
        fullLangAllOperators.push_back(">");
        fullLangAllOperators.push_back("<");
        fullLangAllOperators.push_back(">=");
        fullLangAllOperators.push_back("<=");
        fullLangAllOperators.push_back("&&");
        fullLangAllOperators.push_back("||");
        fullLangAllOperators.push_back("!");
        fullLangAllOperators.push_back("&");
        fullLangAllOperators.push_back("|");
        fullLangAllOperators.push_back("^");
        fullLangAllOperators.push_back("~");
        fullLangAllOperators.push_back("<<");
        fullLangAllOperators.push_back(">>");
        fullLangAllOperators.push_back("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push_back("?");
        fullLangAllOperators.push_back(":");
    }
    if (langToConvertTo == "nim") {
        fullLangAllOperators.push_back("nil");
        fullLangAllOperators.push_back("true");
        fullLangAllOperators.push_back("false");
        fullLangAllOperators.push_back("&");
        fullLangAllOperators.push_back("+");
        fullLangAllOperators.push_back("-");
        fullLangAllOperators.push_back("*");
        fullLangAllOperators.push_back("/");
        fullLangAllOperators.push_back("%");
        fullLangAllOperators.push_back("^");
        fullLangAllOperators.push_back("==");
        fullLangAllOperators.push_back("==");
        fullLangAllOperators.push_back("!=");
        fullLangAllOperators.push_back(">");
        fullLangAllOperators.push_back("<");
        fullLangAllOperators.push_back(">=");
        fullLangAllOperators.push_back("<=");
        fullLangAllOperators.push_back("and");
        fullLangAllOperators.push_back("or");
        fullLangAllOperators.push_back("not");
        fullLangAllOperators.push_back("and");
        fullLangAllOperators.push_back("or");
        fullLangAllOperators.push_back("xor");
        fullLangAllOperators.push_back("not");
        fullLangAllOperators.push_back("shl");
        fullLangAllOperators.push_back("shr");
        fullLangAllOperators.push_back("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push_back("?");
        fullLangAllOperators.push_back(":");
    }
    if (langToConvertTo == "ahk") {
        fullLangAllOperators.push_back(Chr(34) + "" + Chr(34));
        fullLangAllOperators.push_back("true");
        fullLangAllOperators.push_back("false");
        fullLangAllOperators.push_back(".");
        fullLangAllOperators.push_back("+");
        fullLangAllOperators.push_back("-");
        fullLangAllOperators.push_back("*");
        fullLangAllOperators.push_back("/");
        fullLangAllOperators.push_back("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push_back("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push_back("=");
        fullLangAllOperators.push_back("==");
        fullLangAllOperators.push_back("!=");
        fullLangAllOperators.push_back(">");
        fullLangAllOperators.push_back("<");
        fullLangAllOperators.push_back(">=");
        fullLangAllOperators.push_back("<=");
        fullLangAllOperators.push_back("&&");
        fullLangAllOperators.push_back("||");
        fullLangAllOperators.push_back("!");
        fullLangAllOperators.push_back("&");
        fullLangAllOperators.push_back("|");
        fullLangAllOperators.push_back("^");
        fullLangAllOperators.push_back("~");
        fullLangAllOperators.push_back("<<");
        fullLangAllOperators.push_back(">>");
        fullLangAllOperators.push_back("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push_back("?");
        fullLangAllOperators.push_back(":");
    }
    if (langToConvertTo == "swift") {
        fullLangAllOperators.push_back("nil");
        fullLangAllOperators.push_back("true");
        fullLangAllOperators.push_back("false");
        fullLangAllOperators.push_back("+");
        fullLangAllOperators.push_back("+");
        fullLangAllOperators.push_back("-");
        fullLangAllOperators.push_back("*");
        fullLangAllOperators.push_back("/");
        fullLangAllOperators.push_back("%");
        fullLangAllOperators.push_back("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push_back("==");
        fullLangAllOperators.push_back("===");
        fullLangAllOperators.push_back("!=");
        fullLangAllOperators.push_back(">");
        fullLangAllOperators.push_back("<");
        fullLangAllOperators.push_back(">=");
        fullLangAllOperators.push_back("<=");
        fullLangAllOperators.push_back("&&");
        fullLangAllOperators.push_back("||");
        fullLangAllOperators.push_back("!");
        fullLangAllOperators.push_back("&");
        fullLangAllOperators.push_back("|");
        fullLangAllOperators.push_back("^");
        fullLangAllOperators.push_back("~");
        fullLangAllOperators.push_back("<<");
        fullLangAllOperators.push_back(">>");
        fullLangAllOperators.push_back("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push_back("?");
        fullLangAllOperators.push_back(":");
    }
    if (langToConvertTo == "dart") {
        fullLangAllOperators.push_back("null");
        fullLangAllOperators.push_back("true");
        fullLangAllOperators.push_back("false");
        fullLangAllOperators.push_back("+");
        fullLangAllOperators.push_back("+");
        fullLangAllOperators.push_back("-");
        fullLangAllOperators.push_back("*");
        fullLangAllOperators.push_back("/");
        fullLangAllOperators.push_back("%");
        fullLangAllOperators.push_back("THIS OPERATOR DOES NOT EXIST IN THIS LANG SORRY FOR THIS ERROR");
        fullLangAllOperators.push_back("==");
        fullLangAllOperators.push_back("===");
        fullLangAllOperators.push_back("!=");
        fullLangAllOperators.push_back(">");
        fullLangAllOperators.push_back("<");
        fullLangAllOperators.push_back(">=");
        fullLangAllOperators.push_back("<=");
        fullLangAllOperators.push_back("&&");
        fullLangAllOperators.push_back("||");
        fullLangAllOperators.push_back("!");
        fullLangAllOperators.push_back("&");
        fullLangAllOperators.push_back("|");
        fullLangAllOperators.push_back("^");
        fullLangAllOperators.push_back("~");
        fullLangAllOperators.push_back("<<");
        fullLangAllOperators.push_back(">>");
        fullLangAllOperators.push_back(">>>");
        fullLangAllOperators.push_back("?");
        fullLangAllOperators.push_back(":");
    }
    if (langToConvertTo == "ts") {
        fullLangAllOperators.push_back("null");
        fullLangAllOperators.push_back("true");
        fullLangAllOperators.push_back("false");
        fullLangAllOperators.push_back("+");
        fullLangAllOperators.push_back("+");
        fullLangAllOperators.push_back("-");
        fullLangAllOperators.push_back("*");
        fullLangAllOperators.push_back("/");
        fullLangAllOperators.push_back("%");
        fullLangAllOperators.push_back("**");
        if (useJavaScriptAlwaysTripleEqual == "on") {
            fullLangAllOperators.push_back("===");
        } else {
            fullLangAllOperators.push_back("==");
        }
        fullLangAllOperators.push_back("===");
        fullLangAllOperators.push_back("!=");
        fullLangAllOperators.push_back(">");
        fullLangAllOperators.push_back("<");
        fullLangAllOperators.push_back(">=");
        fullLangAllOperators.push_back("<=");
        fullLangAllOperators.push_back("&&");
        fullLangAllOperators.push_back("||");
        fullLangAllOperators.push_back("!");
        fullLangAllOperators.push_back("&");
        fullLangAllOperators.push_back("|");
        fullLangAllOperators.push_back("^");
        fullLangAllOperators.push_back("~");
        fullLangAllOperators.push_back("<<");
        fullLangAllOperators.push_back(">>");
        fullLangAllOperators.push_back(">>>");
        fullLangAllOperators.push_back("?");
        fullLangAllOperators.push_back(":");
    }
    if (langToConvertTo == "groovy") {
        fullLangAllOperators.push_back("null");
        fullLangAllOperators.push_back("true");
        fullLangAllOperators.push_back("false");
        fullLangAllOperators.push_back("+");
        fullLangAllOperators.push_back("+");
        fullLangAllOperators.push_back("-");
        fullLangAllOperators.push_back("*");
        fullLangAllOperators.push_back("/");
        fullLangAllOperators.push_back("%");
        fullLangAllOperators.push_back("**");
        fullLangAllOperators.push_back("==");
        fullLangAllOperators.push_back("==");
        fullLangAllOperators.push_back("!=");
        fullLangAllOperators.push_back(">");
        fullLangAllOperators.push_back("<");
        fullLangAllOperators.push_back(">=");
        fullLangAllOperators.push_back("<=");
        fullLangAllOperators.push_back("&&");
        fullLangAllOperators.push_back("||");
        fullLangAllOperators.push_back("!");
        fullLangAllOperators.push_back("&");
        fullLangAllOperators.push_back("|");
        fullLangAllOperators.push_back("^");
        fullLangAllOperators.push_back("~");
        fullLangAllOperators.push_back("<<");
        fullLangAllOperators.push_back(">>");
        fullLangAllOperators.push_back(">>>");
        fullLangAllOperators.push_back("?");
        fullLangAllOperators.push_back(":");
    }
    if (langToConvertTo == langFileExtension_2) {
        fullLangAllOperators.push_back(keyWordNull_2);
        fullLangAllOperators.push_back(keyWordTrue_2);
        fullLangAllOperators.push_back(keyWordFalse_2);
        fullLangAllOperators.push_back(keyWordConcat_2);
        fullLangAllOperators.push_back(keyWordAdd_2);
        fullLangAllOperators.push_back(keyWordSub_2);
        fullLangAllOperators.push_back(keyWordMul_2);
        fullLangAllOperators.push_back(keyWordDiv_2);
        fullLangAllOperators.push_back(keyWordMod_2);
        fullLangAllOperators.push_back(keyWordExp_2);
        fullLangAllOperators.push_back(keyWordEqual_2);
        fullLangAllOperators.push_back(keyWordStrictEqual_2);
        fullLangAllOperators.push_back(keyWordNotEqual_2);
        fullLangAllOperators.push_back(keyWordGreater_2);
        fullLangAllOperators.push_back(keyWordLess_2);
        fullLangAllOperators.push_back(keyWordGreaterEqual_2);
        fullLangAllOperators.push_back(keyWordLessEqual_2);
        fullLangAllOperators.push_back(keyWordAnd_2);
        fullLangAllOperators.push_back(keyWordOr_2);
        fullLangAllOperators.push_back(keyWordNot_2);
        fullLangAllOperators.push_back(keyWordBitAnd_2);
        fullLangAllOperators.push_back(keyWordBitOr_2);
        fullLangAllOperators.push_back(keyWordBitXor_2);
        fullLangAllOperators.push_back(keyWordBitNot_2);
        fullLangAllOperators.push_back(keyWordShiftLeft_2);
        fullLangAllOperators.push_back(keyWordShiftRight_2);
        fullLangAllOperators.push_back(keyWordShiftUnsignedRight_2);
        fullLangAllOperators.push_back(keyWordTernary1_2);
        fullLangAllOperators.push_back(keyWordTernary2_2);
    }
    return fullLangAllOperators;
}
std::vector<std::string> GETfullLangAllOperators_HELP() {
    std::vector<std::string> fullLangAllOperators_HELP;
    fullLangAllOperators_HELP.push_back(keyWordNull);
    fullLangAllOperators_HELP.push_back(keyWordTrue);
    fullLangAllOperators_HELP.push_back(keyWordFalse);
    fullLangAllOperators_HELP.push_back(keyWordConcat);
    fullLangAllOperators_HELP.push_back(keyWordAdd);
    fullLangAllOperators_HELP.push_back(keyWordSub);
    fullLangAllOperators_HELP.push_back(keyWordMul);
    fullLangAllOperators_HELP.push_back(keyWordDiv);
    fullLangAllOperators_HELP.push_back(keyWordMod);
    fullLangAllOperators_HELP.push_back(keyWordExp);
    fullLangAllOperators_HELP.push_back(keyWordEqual);
    fullLangAllOperators_HELP.push_back(keyWordStrictEqual);
    fullLangAllOperators_HELP.push_back(keyWordNotEqual);
    fullLangAllOperators_HELP.push_back(keyWordGreater);
    fullLangAllOperators_HELP.push_back(keyWordLess);
    fullLangAllOperators_HELP.push_back(keyWordGreaterEqual);
    fullLangAllOperators_HELP.push_back(keyWordLessEqual);
    fullLangAllOperators_HELP.push_back(keyWordAnd);
    fullLangAllOperators_HELP.push_back(keyWordOr);
    fullLangAllOperators_HELP.push_back(keyWordNot);
    fullLangAllOperators_HELP.push_back(keyWordBitAnd);
    fullLangAllOperators_HELP.push_back(keyWordBitOr);
    fullLangAllOperators_HELP.push_back(keyWordBitXor);
    fullLangAllOperators_HELP.push_back(keyWordBitNot);
    fullLangAllOperators_HELP.push_back(keyWordShiftLeft);
    fullLangAllOperators_HELP.push_back(keyWordShiftRight);
    fullLangAllOperators_HELP.push_back(keyWordShiftUnsignedRight);
    fullLangAllOperators_HELP.push_back(keyWordTernary1);
    fullLangAllOperators_HELP.push_back(keyWordTernary2);
    return fullLangAllOperators_HELP;
}
std::string expressionParserTranspiler(std::string expression) {
    std::string fixExpertionLineFuncOnlyTEXT_func = "";
    int fixExpertionLineFuncOnlyTEXT_numDelete = 0;
    if (fixExpertionLineFuncOnly == 1) {
        fixExpertionLineFuncOnlyTEXT_func = StrSplit(expression, "(", 1);
        fixExpertionLineFuncOnlyTEXT_numDelete = StrLen(fixExpertionLineFuncOnlyTEXT_func) + 1;
        expression = StringTrimLeft(expression, fixExpertionLineFuncOnlyTEXT_numDelete);
    }
    if (langToConvertTo != "js" && langToConvertTo != "ts" && langToConvertTo != langFileExtension_2) {
        expression = RegExReplace(expression, "\\b" + keyWordAwait + "\\b", "");
    }
    for (int A_Index62 = 0; A_Index62 < 29 + 0; A_Index62++) {
        if (InStr(expression, fullLangAllOperators_HELP[A_Index62])) {
            if (A_Index62 == 0 || A_Index62 == 1 || A_Index62 == 2) {
                expression = RegExReplace(expression, "\\b" + fullLangAllOperators_HELP[A_Index62] + "\\b", fullLangAllOperators[A_Index62]);
            } else {
                if (A_Index62 == 19) {
                    if (langToConvertTo == "py" || langToConvertTo == "lua" || langToConvertTo == "nim") {
                        expression = RegExReplace(expression, "\\b" + fullLangAllOperators_HELP[A_Index62] + "\\b", "not");
                    } else {
                        expression = RegExReplace(expression, "\\b" + fullLangAllOperators_HELP[A_Index62] + "\\b", "!");
                    }
                    if (langToConvertTo == "py" || langToConvertTo == "lua" || langToConvertTo == "nim") {
                        expression = RegExReplace(expression, "!([\\w]+)", "not $1");
                    }
                    expression = StrReplace(expression, " not= ", " != ");
                } else {
                    expression = StrReplace(expression, " " + fullLangAllOperators_HELP[A_Index62] + " ", " " + fullLangAllOperators[A_Index62] + " ");
                    if (A_Index62 == 28) {
                        if (langToConvertTo == "py") {
                            // Convert C-like ternary to Python ternary using RegExReplace
                            expression = RegExReplace(expression, "(.*?)\\s*\\?\\s*(.*?)\\s*:\\s*(.*?)", "$2 if $1 else $3");
                        }
                        if (langToConvertTo == "nim") {
                            // Convert C-like ternary to Nim ternary using RegExReplace
                            expression = RegExReplace(expression, "(.*?)\\s*\\?\\s*(.*?)\\s*:\\s*(.*)", "if $1: $2 else: $3");
                        }
                        if (langToConvertTo == "lua") {
                            // Convert C-like ternary to Lua ternary-like expression using RegExReplace
                            expression = RegExReplace(expression, "(.*?)\\s*\\?\\s*(.*?)\\s*:\\s*(.*?)", "$1 and $2 or $3");
                        }
                        if (langToConvertTo == "kt") {
                            // Convert C-like ternary to Kotlin ternary-like expression using RegExReplace
                            expression = RegExReplace(expression, "(.*?)\\s*\\?\\s*(.*?)\\s*:\\s*(.*?)", "if $1 $2 else $3");
                        }
                    }
                }
            }
        }
    }
    if (langToConvertTo == "ahk") {
        if (InStr(expression, keyWordAIndex)) {
            expression = RegExReplace(expression, "\\b" + keyWordAIndex + "\\b", "A_Index");
        }
        if (InStr(expression, keyWordALoopField)) {
            expression = RegExReplace(expression, "\\b" + keyWordALoopField + "\\b", "A_LoopField");
        }
    }
    if (langToConvertTo == langFileExtension_2) {
        if (InStr(expression, keyWordAIndex)) {
            expression = RegExReplace(expression, "\\b" + keyWordAIndex + "\\b", keyWordAIndex_2);
        }
        if (InStr(expression, keyWordALoopField)) {
            expression = RegExReplace(expression, "\\b" + keyWordALoopField + "\\b", keyWordALoopField_2);
        }
    }
    if (langToConvertTo != langFileExtension_2 && langToConvertTo != "ahk") {
        if (langToConvertTo == "py" || langToConvertTo == "lua" || langToConvertTo == "nim") {
            expression = StrReplace(expression, ") and (", " and ");
            expression = StrReplace(expression, ") or (", " or ");
        } else {
            expression = StrReplace(expression, ") && (", " && ");
            expression = StrReplace(expression, ") || (", " || ");
        }
    }
    // extra for array methods
    expression = arrayParserTranspiler(expression);
    if (langToConvertTo == "cpp") {
        expression = RegExReplace(expression, "\\b" + theTryCatchVarForErrors + "\\b", theTryCatchVarForErrors + ".what()");
    }
    if (langToConvertTo == "js") {
        expression = RegExReplace(expression, "\\b" + theTryCatchVarForErrors + "\\b", theTryCatchVarForErrors + ".message");
    }
    if (langToConvertTo == "cs") {
        expression = RegExReplace(expression, "\\b" + theTryCatchVarForErrors + "\\b", theTryCatchVarForErrors + ".Message");
    }
    if (langToConvertTo == "java") {
        expression = RegExReplace(expression, "\\b" + theTryCatchVarForErrors + "\\b", theTryCatchVarForErrors + ".getMessage()");
    }
    if (langToConvertTo == "kt") {
        expression = RegExReplace(expression, "\\b" + theTryCatchVarForErrors + "\\b", theTryCatchVarForErrors + ".message");
    }
    if (langToConvertTo == "rb") {
        expression = RegExReplace(expression, "\\b" + theTryCatchVarForErrors + "\\b", theTryCatchVarForErrors + ".message");
    }
    if (langToConvertTo == "nim") {
        expression = RegExReplace(expression, "\\b" + theTryCatchVarForErrors + "\\b", theTryCatchVarForErrors + ".msg");
    }
    if (langToConvertTo == "swift") {
        expression = RegExReplace(expression, "\\b" + theTryCatchVarForErrors + "\\b", theTryCatchVarForErrors + ".localizedDescription");
    }
    if (langToConvertTo == "ts") {
        expression = RegExReplace(expression, "\\b" + theTryCatchVarForErrors + "\\b", theTryCatchVarForErrors + ".message");
    }
    if (langToConvertTo == "groovy") {
        expression = RegExReplace(expression, "\\b" + theTryCatchVarForErrors + "\\b", theTryCatchVarForErrors + ".message");
    }
    if (fixExpertionLineFuncOnly == 1) {
        expression = fixExpertionLineFuncOnlyTEXT_func + "(" + expression;
    }
    return expression;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
std::string compiler(std::string htCode, std::string allInstructionFile, std::string mode, std::string langToConvertToParam = "") {
    std::string instructions = allInstructionFile;
    std::vector<std::string> items63 = LoopParseFunc(allInstructionFile, "\n", "\r");
    for (size_t A_Index63 = 0; A_Index63 < items63.size() + 0; A_Index63++) {
        std::string A_LoopField63 = items63[A_Index63 - 0];
        if (A_Index63 == 0) {
            langToConvertTo = Trim(A_LoopField63);
        }
        if (A_Index63 == 1) {
            langFileExtension = Trim(A_LoopField63);
        }
        if (A_Index63 == 2) {
            commands = Trim(A_LoopField63);
        }
        if (A_Index63 == 3) {
            keyWordAlliance = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 4) {
            keyWordCrew = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 5) {
            keyWordMethod = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 6) {
            keyWordDefObj = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 7) {
            keyWordPorp = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 8) {
            keyWordThis = Trim(A_LoopField63);
        }
        if (A_Index63 == 9) {
            keyWordInclude = Trim(A_LoopField63);
        }
        if (A_Index63 == 10) {
            keyWordCodeInTheTranspiledLangStart = Trim(A_LoopField63);
        }
        if (A_Index63 == 11) {
            keyWordCodeInTheTranspiledLangEnd = Trim(A_LoopField63);
        }
        if (A_Index63 == 12) {
            keyWordCodeInTheTranspiledLangStartCPP = Trim(A_LoopField63);
        }
        if (A_Index63 == 13) {
            keyWordCodeInTheTranspiledLangEndCPP = Trim(A_LoopField63);
        }
        if (A_Index63 == 14) {
            keyWordCodeInTheTranspiledLangStartPY = Trim(A_LoopField63);
        }
        if (A_Index63 == 15) {
            keyWordCodeInTheTranspiledLangEndPY = Trim(A_LoopField63);
        }
        if (A_Index63 == 16) {
            keyWordCodeInTheTranspiledLangStartJS = Trim(A_LoopField63);
        }
        if (A_Index63 == 17) {
            keyWordCodeInTheTranspiledLangEndJS = Trim(A_LoopField63);
        }
        if (A_Index63 == 18) {
            keyWordCodeInTheTranspiledLangStartGO = Trim(A_LoopField63);
        }
        if (A_Index63 == 19) {
            keyWordCodeInTheTranspiledLangEndGO = Trim(A_LoopField63);
        }
        if (A_Index63 == 20) {
            keyWordCodeInTheTranspiledLangStartLUA = Trim(A_LoopField63);
        }
        if (A_Index63 == 21) {
            keyWordCodeInTheTranspiledLangEndLUA = Trim(A_LoopField63);
        }
        if (A_Index63 == 22) {
            keyWordCodeInTheTranspiledLangStartCS = Trim(A_LoopField63);
        }
        if (A_Index63 == 23) {
            keyWordCodeInTheTranspiledLangEndCS = Trim(A_LoopField63);
        }
        if (A_Index63 == 24) {
            keyWordCodeInTheTranspiledLangStartJAVA = Trim(A_LoopField63);
        }
        if (A_Index63 == 25) {
            keyWordCodeInTheTranspiledLangEndJAVA = Trim(A_LoopField63);
        }
        if (A_Index63 == 26) {
            keyWordCodeInTheTranspiledLangStartKT = Trim(A_LoopField63);
        }
        if (A_Index63 == 27) {
            keyWordCodeInTheTranspiledLangEndKT = Trim(A_LoopField63);
        }
        if (A_Index63 == 28) {
            keyWordCodeInTheTranspiledLangStartRB = Trim(A_LoopField63);
        }
        if (A_Index63 == 29) {
            keyWordCodeInTheTranspiledLangEndRB = Trim(A_LoopField63);
        }
        if (A_Index63 == 30) {
            keyWordCodeInTheTranspiledLangStartNIM = Trim(A_LoopField63);
        }
        if (A_Index63 == 31) {
            keyWordCodeInTheTranspiledLangEndNIM = Trim(A_LoopField63);
        }
        if (A_Index63 == 32) {
            keyWordCodeInTheTranspiledLangStartAHK = Trim(A_LoopField63);
        }
        if (A_Index63 == 33) {
            keyWordCodeInTheTranspiledLangEndAHK = Trim(A_LoopField63);
        }
        if (A_Index63 == 34) {
            keyWordCodeInTheTranspiledLangStartSWIFT = Trim(A_LoopField63);
        }
        if (A_Index63 == 35) {
            keyWordCodeInTheTranspiledLangEndSWIFT = Trim(A_LoopField63);
        }
        if (A_Index63 == 36) {
            keyWordCodeInTheTranspiledLangStartDART = Trim(A_LoopField63);
        }
        if (A_Index63 == 37) {
            keyWordCodeInTheTranspiledLangEndDART = Trim(A_LoopField63);
        }
        if (A_Index63 == 38) {
            keyWordCodeInTheTranspiledLangStartTS = Trim(A_LoopField63);
        }
        if (A_Index63 == 39) {
            keyWordCodeInTheTranspiledLangEndTS = Trim(A_LoopField63);
        }
        if (A_Index63 == 40) {
            keyWordCodeInTheTranspiledLangStartGROOVY = Trim(A_LoopField63);
        }
        if (A_Index63 == 41) {
            keyWordCodeInTheTranspiledLangEndGROOVY = Trim(A_LoopField63);
        }
        if (A_Index63 == 42) {
            keyWordCodeInTheTranspiledLangStartHTVM = Trim(A_LoopField63);
        }
        if (A_Index63 == 43) {
            keyWordCodeInTheTranspiledLangEndHTVM = Trim(A_LoopField63);
        }
        if (A_Index63 == 44) {
            keyWordCodeInHTVMstart = Trim(A_LoopField63);
        }
        if (A_Index63 == 45) {
            keyWordCodeInHTVMend = Trim(A_LoopField63);
        }
        if (A_Index63 == 46) {
            keyWordCurlyBraceOpen = Trim(A_LoopField63);
        }
        if (A_Index63 == 47) {
            keyWordCurlyBraceClose = Trim(A_LoopField63);
        }
        if (A_Index63 == 48) {
            keyWordNull = Trim(A_LoopField63);
        }
        if (A_Index63 == 49) {
            keyWordTrue = Trim(A_LoopField63);
        }
        if (A_Index63 == 50) {
            keyWordFalse = Trim(A_LoopField63);
        }
        if (A_Index63 == 51) {
            keyWordVoid = Trim(A_LoopField63);
        }
        if (A_Index63 == 52) {
            keyWordDouble = Trim(A_LoopField63);
        }
        if (A_Index63 == 53) {
            keyWordChar = Trim(A_LoopField63);
        }
        if (A_Index63 == 54) {
            keyWordUint8 = Trim(A_LoopField63);
        }
        if (A_Index63 == 55) {
            keyWordUint16 = Trim(A_LoopField63);
        }
        if (A_Index63 == 56) {
            keyWordUint32 = Trim(A_LoopField63);
        }
        if (A_Index63 == 57) {
            keyWordUint64 = Trim(A_LoopField63);
        }
        if (A_Index63 == 58) {
            keyWordINT = Trim(A_LoopField63);
        }
        if (A_Index63 == 59) {
            keyWordSTR = Trim(A_LoopField63);
        }
        if (A_Index63 == 60) {
            keyWordBOOL = Trim(A_LoopField63);
        }
        if (A_Index63 == 61) {
            keyWordFLOAT = Trim(A_LoopField63);
        }
        if (A_Index63 == 62) {
            keyWordINT8 = Trim(A_LoopField63);
        }
        if (A_Index63 == 63) {
            keyWordINT16 = Trim(A_LoopField63);
        }
        if (A_Index63 == 64) {
            keyWordINT32 = Trim(A_LoopField63);
        }
        if (A_Index63 == 65) {
            keyWordINT64 = Trim(A_LoopField63);
        }
        if (A_Index63 == 66) {
            keyWordIF = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 67) {
            keyWordElseIf = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 68) {
            keyWordElse = Trim(A_LoopField63);
        }
        if (A_Index63 == 69) {
            keyWordWhileLoop = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 70) {
            keyWordLoopInfinite = Trim(A_LoopField63);
        }
        if (A_Index63 == 71) {
            keyWordLoop = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 72) {
            keyWordLoopParse = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 73) {
            keyWordContinue = Trim(A_LoopField63);
        }
        if (A_Index63 == 74) {
            keyWordBreak = Trim(A_LoopField63);
        }
        if (A_Index63 == 75) {
            keyWordFunc = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 76) {
            keyWordAwait = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 77) {
            keyWordAsync = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 78) {
            keyWordThrow = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 79) {
            keyWordErrorMsg = Trim(A_LoopField63);
        }
        if (A_Index63 == 80) {
            keyWordTry = Trim(A_LoopField63);
        }
        if (A_Index63 == 81) {
            keyWordCatch = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 82) {
            keyWordFinally = Trim(A_LoopField63);
        }
        if (A_Index63 == 83) {
            keyWordReturnStatement = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 84) {
            keyWordArrayAppend = Trim(A_LoopField63);
        }
        if (A_Index63 == 85) {
            keyWordArrayPop = Trim(A_LoopField63);
        }
        if (A_Index63 == 86) {
            keyWordArraySize = Trim(A_LoopField63);
        }
        if (A_Index63 == 87) {
            keyWordArrayInsert = Trim(A_LoopField63);
        }
        if (A_Index63 == 88) {
            keyWordArrayRemove = Trim(A_LoopField63);
        }
        if (A_Index63 == 89) {
            keyWordArrayIndexOf = Trim(A_LoopField63);
        }
        if (A_Index63 == 90) {
            keyWordArrayDefinition = Trim(A_LoopField63);
        }
        if (A_Index63 == 91) {
            keyWordArrayOfIntegersDefinition = Trim(A_LoopField63);
        }
        if (A_Index63 == 92) {
            keyWordArrayOfStringsDefinition = Trim(A_LoopField63);
        }
        if (A_Index63 == 93) {
            keyWordArrayOfFloatingPointNumbersDefinition = Trim(A_LoopField63);
        }
        if (A_Index63 == 94) {
            keyWordArrayOfBooleansDefinition = Trim(A_LoopField63);
        }
        if (A_Index63 == 95) {
            keyWordVar = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 96) {
            keyWordLet = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 97) {
            keyWordConst = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 98) {
            keyWordEnd = Trim(A_LoopField63);
        }
        if (A_Index63 == 99) {
            keyWordGlobal = Trim(A_LoopField63) + " ";
        }
        if (A_Index63 == 100) {
            keyWordComment = Trim(A_LoopField63);
        }
        if (A_Index63 == 101) {
            keyWordCommentOpenMultiLine = Trim(A_LoopField63);
        }
        if (A_Index63 == 102) {
            keyWordCommentCloseMultiLine = Trim(A_LoopField63);
        }
        if (A_Index63 == 103) {
            keyWordEscpaeChar = Trim(A_LoopField63);
        }
        if (A_Index63 == 104) {
            keyWordMainLabel = Trim(A_LoopField63);
        }
        if (A_Index63 == 105) {
            keyWordConcat = Trim(A_LoopField63);
        }
        if (A_Index63 == 106) {
            keyWordAdd = Trim(A_LoopField63);
        }
        if (A_Index63 == 107) {
            keyWordSub = Trim(A_LoopField63);
        }
        if (A_Index63 == 108) {
            keyWordMul = Trim(A_LoopField63);
        }
        if (A_Index63 == 109) {
            keyWordDiv = Trim(A_LoopField63);
        }
        if (A_Index63 == 110) {
            keyWordMod = Trim(A_LoopField63);
        }
        if (A_Index63 == 111) {
            keyWordExp = Trim(A_LoopField63);
        }
        if (A_Index63 == 112) {
            keyWordEqual = Trim(A_LoopField63);
        }
        if (A_Index63 == 113) {
            keyWordStrictEqual = Trim(A_LoopField63);
        }
        if (A_Index63 == 114) {
            keyWordNotEqual = Trim(A_LoopField63);
        }
        if (A_Index63 == 115) {
            keyWordGreater = Trim(A_LoopField63);
        }
        if (A_Index63 == 116) {
            keyWordLess = Trim(A_LoopField63);
        }
        if (A_Index63 == 117) {
            keyWordGreaterEqual = Trim(A_LoopField63);
        }
        if (A_Index63 == 118) {
            keyWordLessEqual = Trim(A_LoopField63);
        }
        if (A_Index63 == 119) {
            keyWordAnd = Trim(A_LoopField63);
        }
        if (A_Index63 == 120) {
            keyWordOr = Trim(A_LoopField63);
        }
        if (A_Index63 == 121) {
            keyWordNot = Trim(A_LoopField63);
        }
        if (A_Index63 == 122) {
            keyWordBitAnd = Trim(A_LoopField63);
        }
        if (A_Index63 == 123) {
            keyWordBitOr = Trim(A_LoopField63);
        }
        if (A_Index63 == 124) {
            keyWordBitXor = Trim(A_LoopField63);
        }
        if (A_Index63 == 125) {
            keyWordBitNot = Trim(A_LoopField63);
        }
        if (A_Index63 == 126) {
            keyWordShiftLeft = Trim(A_LoopField63);
        }
        if (A_Index63 == 127) {
            keyWordShiftRight = Trim(A_LoopField63);
        }
        if (A_Index63 == 128) {
            keyWordShiftUnsignedRight = Trim(A_LoopField63);
        }
        if (A_Index63 == 129) {
            keyWordAssign = Trim(A_LoopField63);
        }
        if (A_Index63 == 130) {
            keyWordAssignAdd = Trim(A_LoopField63);
        }
        if (A_Index63 == 131) {
            keyWordAssignConcat = Trim(A_LoopField63);
        }
        if (A_Index63 == 132) {
            keyWordAssignSub = Trim(A_LoopField63);
        }
        if (A_Index63 == 133) {
            keyWordAssignMul = Trim(A_LoopField63);
        }
        if (A_Index63 == 134) {
            keyWordAssignDiv = Trim(A_LoopField63);
        }
        if (A_Index63 == 135) {
            keyWordAssignMod = Trim(A_LoopField63);
        }
        if (A_Index63 == 136) {
            keyWordAssignShiftLeft = Trim(A_LoopField63);
        }
        if (A_Index63 == 137) {
            keyWordAssignShiftRight = Trim(A_LoopField63);
        }
        if (A_Index63 == 138) {
            keyWordLogicalAssignShiftRight = Trim(A_LoopField63);
        }
        if (A_Index63 == 139) {
            keyWordAssignBitAnd = Trim(A_LoopField63);
        }
        if (A_Index63 == 140) {
            keyWordAssignBitOr = Trim(A_LoopField63);
        }
        if (A_Index63 == 141) {
            keyWordAssignBitXor = Trim(A_LoopField63);
        }
        if (A_Index63 == 142) {
            keyWordTernary1 = Trim(A_LoopField63);
        }
        if (A_Index63 == 143) {
            keyWordTernary2 = Trim(A_LoopField63);
        }
        if (A_Index63 == 144) {
            keyWordInc = Trim(A_LoopField63);
        }
        if (A_Index63 == 145) {
            keyWordDec = Trim(A_LoopField63);
        }
        if (A_Index63 == 146) {
            AHKlikeLoopsIndexedAt = Trim(A_LoopField63);
        }
        if (A_Index63 == 147) {
            keyWordAIndex = Trim(A_LoopField63);
        }
        if (A_Index63 == 148) {
            keyWordALoopField = Trim(A_LoopField63);
        }
        if (A_Index63 == 149) {
            useCurlyBraces = Trim(A_LoopField63);
        }
        if (A_Index63 == 150) {
            useEnd = Trim(A_LoopField63);
        }
        if (A_Index63 == 151) {
            useSemicolon = Trim(A_LoopField63);
        }
        if (A_Index63 == 152) {
            useParentheses = Trim(A_LoopField63);
        }
        if (A_Index63 == 153) {
            usePrefixTypeForTypeDefinition = Trim(A_LoopField63);
        }
        if (A_Index63 == 154) {
            usePostfixTypeForTypeDefinition = Trim(A_LoopField63);
        }
        if (A_Index63 == 155) {
            usePythonicColonSyntax = Trim(A_LoopField63);
        }
        if (A_Index63 == 156) {
            useCurlyBracesSyntaxForArrayDef = Trim(A_LoopField63);
        }
        if (A_Index63 == 157) {
            useInJavaScriptAlwaysUseVar = Trim(A_LoopField63);
        }
        if (A_Index63 == 158) {
            useJavaScriptInAfullHTMLfile = Trim(A_LoopField63);
        }
        if (A_Index63 == 159) {
            useJavaScriptAmainFuncDef = Trim(A_LoopField63);
        }
        if (A_Index63 == 160) {
            useJavaScriptAllFuncsAreAsync = Trim(A_LoopField63);
        }
        if (A_Index63 == 161) {
            useJavaScriptAlwaysTripleEqual = Trim(A_LoopField63);
        }
    }
    if (argHTVMinstrMORE.size() > 0) {
        std::string allInstructionFile_2 = Trim(FileRead(Trim(argHTVMinstrMORE[0])));
        std::vector<std::string> items64 = LoopParseFunc(allInstructionFile_2, "\n", "\r");
        for (size_t A_Index64 = 0; A_Index64 < items64.size() + 0; A_Index64++) {
            std::string A_LoopField64 = items64[A_Index64 - 0];
            if (A_Index64 == 0) {
                langToConvertTo_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 1) {
                langFileExtension_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 2) {
                commands_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 3) {
                keyWordAlliance_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 4) {
                keyWordCrew_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 5) {
                keyWordMethod_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 6) {
                keyWordDefObj_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 7) {
                keyWordPorp_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 8) {
                keyWordThis_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 9) {
                keyWordInclude_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 10) {
                keyWordCodeInTheTranspiledLangStart_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 11) {
                keyWordCodeInTheTranspiledLangEnd_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 12) {
                keyWordCodeInTheTranspiledLangStartCPP_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 13) {
                keyWordCodeInTheTranspiledLangEndCPP_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 14) {
                keyWordCodeInTheTranspiledLangStartPY_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 15) {
                keyWordCodeInTheTranspiledLangEndPY_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 16) {
                keyWordCodeInTheTranspiledLangStartJS_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 17) {
                keyWordCodeInTheTranspiledLangEndJS_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 18) {
                keyWordCodeInTheTranspiledLangStartGO_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 19) {
                keyWordCodeInTheTranspiledLangEndGO_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 20) {
                keyWordCodeInTheTranspiledLangStartLUA_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 21) {
                keyWordCodeInTheTranspiledLangEndLUA_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 22) {
                keyWordCodeInTheTranspiledLangStartCS_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 23) {
                keyWordCodeInTheTranspiledLangEndCS_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 24) {
                keyWordCodeInTheTranspiledLangStartJAVA_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 25) {
                keyWordCodeInTheTranspiledLangEndJAVA_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 26) {
                keyWordCodeInTheTranspiledLangStartKT_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 27) {
                keyWordCodeInTheTranspiledLangEndKT_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 28) {
                keyWordCodeInTheTranspiledLangStartRB_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 29) {
                keyWordCodeInTheTranspiledLangEndRB_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 30) {
                keyWordCodeInTheTranspiledLangStartNIM_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 31) {
                keyWordCodeInTheTranspiledLangEndNIM_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 32) {
                keyWordCodeInTheTranspiledLangStartAHK_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 33) {
                keyWordCodeInTheTranspiledLangEndAHK_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 34) {
                keyWordCodeInTheTranspiledLangStartSWIFT_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 35) {
                keyWordCodeInTheTranspiledLangEndSWIFT_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 36) {
                keyWordCodeInTheTranspiledLangStartDART_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 37) {
                keyWordCodeInTheTranspiledLangEndDART_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 38) {
                keyWordCodeInTheTranspiledLangStartTS_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 39) {
                keyWordCodeInTheTranspiledLangEndTS_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 40) {
                keyWordCodeInTheTranspiledLangStartGROOVY_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 41) {
                keyWordCodeInTheTranspiledLangEndGROOVY_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 42) {
                keyWordCodeInTheTranspiledLangStartHTVM_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 43) {
                keyWordCodeInTheTranspiledLangEndHTVM_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 44) {
                keyWordCodeInHTVMstart_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 45) {
                keyWordCodeInHTVMend_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 46) {
                keyWordCurlyBraceOpen_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 47) {
                keyWordCurlyBraceClose_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 48) {
                keyWordNull_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 49) {
                keyWordTrue_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 50) {
                keyWordFalse_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 51) {
                keyWordVoid_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 52) {
                keyWordDouble_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 53) {
                keyWordChar_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 54) {
                keyWordUint8_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 55) {
                keyWordUint16_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 56) {
                keyWordUint32_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 57) {
                keyWordUint64_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 58) {
                keyWordINT_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 59) {
                keyWordSTR_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 60) {
                keyWordBOOL_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 61) {
                keyWordFLOAT_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 62) {
                keyWordINT8_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 63) {
                keyWordINT16_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 64) {
                keyWordINT32_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 65) {
                keyWordINT64_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 66) {
                keyWordIF_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 67) {
                keyWordElseIf_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 68) {
                keyWordElse_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 69) {
                keyWordWhileLoop_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 70) {
                keyWordLoopInfinite_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 71) {
                keyWordLoop_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 72) {
                keyWordLoopParse_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 73) {
                keyWordContinue_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 74) {
                keyWordBreak_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 75) {
                keyWordFunc_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 76) {
                keyWordAwait_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 77) {
                keyWordAsync_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 78) {
                keyWordThrow_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 79) {
                keyWordErrorMsg_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 80) {
                keyWordTry_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 81) {
                keyWordCatch_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 82) {
                keyWordFinally_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 83) {
                keyWordReturnStatement_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 84) {
                keyWordArrayAppend_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 85) {
                keyWordArrayPop_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 86) {
                keyWordArraySize_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 87) {
                keyWordArrayInsert_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 88) {
                keyWordArrayRemove_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 89) {
                keyWordArrayIndexOf_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 90) {
                keyWordArrayDefinition_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 91) {
                keyWordArrayOfIntegersDefinition_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 92) {
                keyWordArrayOfStringsDefinition_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 93) {
                keyWordArrayOfFloatingPointNumbersDefinition_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 94) {
                keyWordArrayOfBooleansDefinition_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 95) {
                keyWordVar_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 96) {
                keyWordLet_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 97) {
                keyWordConst_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 98) {
                keyWordEnd_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 99) {
                keyWordGlobal_2 = Trim(A_LoopField64) + " ";
            }
            if (A_Index64 == 100) {
                keyWordComment_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 101) {
                keyWordCommentOpenMultiLine_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 102) {
                keyWordCommentCloseMultiLine_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 103) {
                keyWordEscpaeChar_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 104) {
                keyWordMainLabel_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 105) {
                keyWordConcat_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 106) {
                keyWordAdd_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 107) {
                keyWordSub_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 108) {
                keyWordMul_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 109) {
                keyWordDiv_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 110) {
                keyWordMod_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 111) {
                keyWordExp_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 112) {
                keyWordEqual_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 113) {
                keyWordStrictEqual_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 114) {
                keyWordNotEqual_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 115) {
                keyWordGreater_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 116) {
                keyWordLess_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 117) {
                keyWordGreaterEqual_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 118) {
                keyWordLessEqual_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 119) {
                keyWordAnd_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 120) {
                keyWordOr_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 121) {
                keyWordNot_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 122) {
                keyWordBitAnd_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 123) {
                keyWordBitOr_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 124) {
                keyWordBitXor_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 125) {
                keyWordBitNot_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 126) {
                keyWordShiftLeft_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 127) {
                keyWordShiftRight_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 128) {
                keyWordShiftUnsignedRight_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 129) {
                keyWordAssign_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 130) {
                keyWordAssignAdd_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 131) {
                keyWordAssignConcat_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 132) {
                keyWordAssignSub_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 133) {
                keyWordAssignMul_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 134) {
                keyWordAssignDiv_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 135) {
                keyWordAssignMod_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 136) {
                keyWordAssignShiftLeft_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 137) {
                keyWordAssignShiftRight_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 138) {
                keyWordLogicalAssignShiftRight_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 139) {
                keyWordAssignBitAnd_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 140) {
                keyWordAssignBitOr_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 141) {
                keyWordAssignBitXor_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 142) {
                keyWordTernary1_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 143) {
                keyWordTernary2_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 144) {
                keyWordInc_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 145) {
                keyWordDec_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 146) {
                AHKlikeLoopsIndexedAt_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 147) {
                keyWordAIndex_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 148) {
                keyWordALoopField_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 149) {
                useCurlyBraces_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 150) {
                useEnd_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 151) {
                useSemicolon_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 152) {
                useParentheses_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 153) {
                usePrefixTypeForTypeDefinition_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 154) {
                usePostfixTypeForTypeDefinition_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 155) {
                usePythonicColonSyntax_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 156) {
                useCurlyBracesSyntaxForArrayDef_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 157) {
                useInJavaScriptAlwaysUseVar_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 158) {
                useJavaScriptInAfullHTMLfile_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 159) {
                useJavaScriptAmainFuncDef_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 160) {
                useJavaScriptAllFuncsAreAsync_2 = Trim(A_LoopField64);
            }
            if (A_Index64 == 161) {
                useJavaScriptAlwaysTripleEqual_2 = Trim(A_LoopField64);
            }
        }
    }
    if (Trim(langToConvertToParam) != "") {
        langToConvertTo = Trim(langToConvertToParam);
    }
    int isFullHTVMCode = 0;
    int isNotHTVMfile = 0;
    if (Trim(mode) == "full") {
        isFullHTVMCode = 1;
    } else {
        isFullHTVMCode = 0;
    }
    if (Trim(mode) == "notHTVM") {
        isNotHTVMfile = 1;
    } else {
        isNotHTVMfile = 0;
    }
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    /*
    if (langToConvertTo == langFileExtension_2) {
    }
    if (langToConvertTo == "cpp") {
    }
    if (langToConvertTo == "py") {
    }
    if (langToConvertTo == "js") {
    }
    if (langToConvertTo == "go") {
    }
    if (langToConvertTo == "lua") {
    }
    if (langToConvertTo == "cs") {
    }
    if (langToConvertTo == "java") {
    }
    if (langToConvertTo == "kt") {
    }
    if (langToConvertTo == "rb") {
    }
    if (langToConvertTo == "nim") {
    }
    if (langToConvertTo == "ahk") {
    }
    if (langToConvertTo == "swift") {
    }
    if (langToConvertTo == "dart") {
    }
    if (langToConvertTo == "ts") {
    }
    if (langToConvertTo == "groovy") {
    }
    */
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
    std::string HTVMout = "";
    htCode = Trim(StrReplace(htCode, Chr(13), ""));
    std::string code = "";
    print(htCode);
    code = htCode;
    print(mode);
    print(langToConvertTo);
    print("==================================");
    print("==================================");
    print("==================================");
    print("==================================");
    print("==================================");
    //print(allInstructionFile)
    int haveWeEverUsedAloop = 0;
    int lineDone = 0;
    std::string var1 = "";
    std::string nothing = "";
    int AindexcharLength = 1;
    std::string AindexcharLengthStr = "";
    std::string theFixTextLoopNL = "";
    int htCodeAcurlyBraceAddSomeVrasFixNL = 0;
    std::string htCodeLoopfixa = "";
    std::string htCodeLoopfixa1 = "";
    std::string str123 = "";
    std::string out2 = "";
    std::string myVar = "";
    std::string lineYGI = "";
    std::string line = "";
    std::string line1 = "";
    std::string line2 = "";
    std::string line3 = "";
    std::string itemsOut = "";
    std::string var1out = "";
    std::string theFixTextLoopLP = "";
    int htCodeAcurlyBraceAddSomeVrasFixLP = 0;
    int AIndexLoopCurlyFix = 0;
    std::string sstr123 = "";
    std::string fixLoopLokingFor = "";
    int fixLoopLokingForfound = 0;
    std::string out1 = "";
    int wasAtanyIfsElseAddAIndexLoopCurlyFix = 0;
    int inTarget = 0;
    int insideBracket = 0;
    int netsedCurly = 0;
    int eldLoopNestedBADlol = 0;
    int readyToEnd = 0;
    int endBracketDOntPutThere = 0;
    int dontSaveStr = 0;
    int weAreDoneHereCurly = 0;
    int DeleayOneCuzOfLoopParse = 0;
    int fixLoopLokingForNum = 0;
    int insdeAnestedLoopBAD = 0;
    int foundTheTopLoop = 0;
    std::string out4758686d86d86d86578991a;
    std::string ALoopField = "";
    std::string out1z = "";
    int insideBracket1 = 0;
    int netsedCurly1 = 0;
    int readyToEnd1 = 0;
    std::string strstysrstsytTRIMHELP = "";
    std::string out4758686d86dgt8r754444444 = "";
    int hold = 0;
    std::string holdText = "";
    int ignore = 0;
    std::string htCodeOut1234565432 = "";
    std::string out = "";
    std::string s = "";
    int skipLeftCuleyForFuncPLS = 0;
    // keyWordInclude
    // keyWordInclude
    // keyWordInclude
    std::string allLibCODE = "";
    std::string allLibCODEfix = "";
    std::vector<std::string> allLibsWeSee;
    std::vector<std::string> allLibsWeSeeSEE;
    std::string allLibsWeSeeHOLD = "";
    int doseCodeHaveLibs = 0;
    int doseCodeHaveLibs_HAS_SEEN = 0;
    int doseCodeHaveLibs_HAS_SEEN2 = 0;
    if (isNotHTVMfile == 0) {
        if (langToConvertTo != langFileExtension_2) {
            if (InStr(code, StrLower(keyWordInclude + " "))) {
                for (int A_Index65 = 0; A_Index65 < 10000 + 0; A_Index65++) {
                    doseCodeHaveLibs = 0;
                    allLibCODE = "";
                    if (A_Index65 == 0) {
                        std::vector<std::string> items66 = LoopParseFunc(code, "\n", "\r");
                        for (size_t A_Index66 = 0; A_Index66 < items66.size() + 0; A_Index66++) {
                            std::string A_LoopField66 = items66[A_Index66 - 0];
                            if (SubStr(StrLower(Trim(A_LoopField66)), 1, StrLen(StrLower(keyWordInclude + " "))) == StrLower(keyWordInclude + " ")) {
                                allLibsWeSee.push_back(StrReplace(StringTrimLeft(Trim(A_LoopField66), StrLen(StrLower(keyWordInclude) + " ")), Chr(34), ""));
                                allLibsWeSeeSEE.push_back(StrReplace(StringTrimLeft(Trim(A_LoopField66), StrLen(StrLower(keyWordInclude) + " ")), Chr(34), ""));
                                doseCodeHaveLibs = 1;
                            }
                        }
                    } else {
                        std::vector<std::string> items67 = LoopParseFunc(code, "\n", "\r");
                        for (size_t A_Index67 = 0; A_Index67 < items67.size() + 0; A_Index67++) {
                            std::string A_LoopField67 = items67[A_Index67 - 0];
                            ALoopField = A_LoopField67;
                            if (SubStr(StrLower(Trim(A_LoopField67)), 1, StrLen(StrLower(keyWordInclude + " "))) == StrLower(keyWordInclude + " ")) {
                                doseCodeHaveLibs_HAS_SEEN = 0;
                                for (int A_Index68 = 0; A_Index68 < allLibsWeSee.size() + 0; A_Index68++) {
                                    if (StrReplace(StringTrimLeft(Trim(ALoopField), StrLen(StrLower(keyWordInclude) + " ")), Chr(34), "") == allLibsWeSee[A_Index68]) {
                                        doseCodeHaveLibs_HAS_SEEN = 1;
                                    }
                                }
                                if (doseCodeHaveLibs_HAS_SEEN == 0) {
                                    allLibsWeSee.push_back(StrReplace(StringTrimLeft(Trim(A_LoopField67), StrLen(StrLower(keyWordInclude) + " ")), Chr(34), ""));
                                    allLibsWeSeeSEE.push_back(StrReplace(StringTrimLeft(Trim(A_LoopField67), StrLen(StrLower(keyWordInclude) + " ")), Chr(34), ""));
                                    doseCodeHaveLibs = 1;
                                }
                            }
                        }
                    }
                    for (int A_Index69 = 0; A_Index69 < allLibsWeSee.size() + 0; A_Index69++) {
                        allLibsWeSeeHOLD = allLibsWeSee[A_Index69];
                        doseCodeHaveLibs_HAS_SEEN2 = 0;
                        for (int A_Index70 = 0; A_Index70 < allLibsWeSeeSEE.size() - allLibsWeSee.size() + 0; A_Index70++) {
                            if (allLibsWeSeeHOLD == allLibsWeSeeSEE[A_Index70]) {
                                doseCodeHaveLibs_HAS_SEEN2 = 1;
                            }
                        }
                        if (doseCodeHaveLibs_HAS_SEEN2 == 0) {
                            allLibCODE += FileRead(Trim(allLibsWeSee[allLibsWeSee.size() - A_Index69 - 1])) + "\n";
                        }
                        allLibsWeSee.pop_back();
                    }
                    allLibCODEfix = "";
                    std::vector<std::string> items71 = LoopParseFunc(code, "\n", "\r");
                    for (size_t A_Index71 = 0; A_Index71 < items71.size() + 0; A_Index71++) {
                        std::string A_LoopField71 = items71[A_Index71 - 0];
                        if (SubStr(StrLower(Trim(A_LoopField71)), 1, StrLen(StrLower(keyWordInclude + " "))) != StrLower(keyWordInclude + " ")) {
                            allLibCODEfix += A_LoopField71 + "\n";
                        }
                    }
                    code = StringTrimRight(allLibCODEfix, 1);
                    code = allLibCODE + code;
                    if (doseCodeHaveLibs == 0) {
                        break;
                    }
                }
            }
        }
        ALoopField = "";
    }
    // keyWordInclude
    // keyWordInclude
    // keyWordInclude
    // PROGRAMMING BLOCK
    // PROGRAMMING BLOCK
    // PROGRAMMING BLOCK
    // PROGRAMMING BLOCK
    int COUNT_programmingBlock_InTheTranspiledLang = 0;
    int COUNT_programmingBlock_CPP = 0;
    int COUNT_programmingBlock_PY = 0;
    int COUNT_programmingBlock_JS = 0;
    int COUNT_programmingBlock_GO = 0;
    int COUNT_programmingBlock_LUA = 0;
    int COUNT_programmingBlock_CS = 0;
    int COUNT_programmingBlock_JAVA = 0;
    int COUNT_programmingBlock_KT = 0;
    int COUNT_programmingBlock_RB = 0;
    int COUNT_programmingBlock_NIM = 0;
    int COUNT_programmingBlock_AHK = 0;
    int COUNT_programmingBlock_SWIFT = 0;
    int COUNT_programmingBlock_DART = 0;
    int COUNT_programmingBlock_TS = 0;
    int COUNT_programmingBlock_GROOVY = 0;
    int COUNT_programmingBlock_HTVM = 0;
    int COUNT_programmingBlock_HTVMsyntax = 0;
    std::string programmingBlocksTemp = "";
    int inProgarmmingBlock = 0;
    std::string holdTempDataProgrammingBlockThenPutInArr = "";
    std::vector<std::string> items72 = LoopParseFunc(code, "\n", "\r");
    for (size_t A_Index72 = 0; A_Index72 < items72.size() + 0; A_Index72++) {
        std::string A_LoopField72 = items72[A_Index72 - 0];
        if (Trim(StrLower(A_LoopField72)) == StrLower(keyWordCodeInTheTranspiledLangEnd)) {
            COUNT_programmingBlock_InTheTranspiledLang++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_InTheTranspiledLang-programmingBlock_InTheTranspiledLang-AA" + STR(COUNT_programmingBlock_InTheTranspiledLang) + "AA\n";
            programmingBlock_InTheTranspiledLang.push_back(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField72)) == StrLower(keyWordCodeInTheTranspiledLangEndCPP)) {
            COUNT_programmingBlock_CPP++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_CPP-programmingBlock_CPP-AA" + STR(COUNT_programmingBlock_CPP) + "AA\n";
            programmingBlock_CPP.push_back(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField72)) == StrLower(keyWordCodeInTheTranspiledLangEndPY)) {
            COUNT_programmingBlock_PY++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_PY-programmingBlock_PY-AA" + STR(COUNT_programmingBlock_PY) + "AA\n";
            programmingBlock_PY.push_back(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField72)) == StrLower(keyWordCodeInTheTranspiledLangEndJS)) {
            COUNT_programmingBlock_JS++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_JS-programmingBlock_JS-AA" + STR(COUNT_programmingBlock_JS) + "AA\n";
            programmingBlock_JS.push_back(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField72)) == StrLower(keyWordCodeInTheTranspiledLangEndGO)) {
            COUNT_programmingBlock_GO++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_GO-programmingBlock_GO-AA" + STR(COUNT_programmingBlock_GO) + "AA\n";
            programmingBlock_GO.push_back(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField72)) == StrLower(keyWordCodeInTheTranspiledLangEndLUA)) {
            COUNT_programmingBlock_LUA++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_LUA-programmingBlock_LUA-AA" + STR(COUNT_programmingBlock_LUA) + "AA\n";
            programmingBlock_LUA.push_back(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField72)) == StrLower(keyWordCodeInTheTranspiledLangEndCS)) {
            COUNT_programmingBlock_CS++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_CS-programmingBlock_CS-AA" + STR(COUNT_programmingBlock_CS) + "AA\n";
            programmingBlock_CS.push_back(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField72)) == StrLower(keyWordCodeInTheTranspiledLangEndJAVA)) {
            COUNT_programmingBlock_JAVA++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_JAVA-programmingBlock_JAVA-AA" + STR(COUNT_programmingBlock_JAVA) + "AA\n";
            programmingBlock_JAVA.push_back(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField72)) == StrLower(keyWordCodeInTheTranspiledLangEndKT)) {
            COUNT_programmingBlock_KT++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_KT-programmingBlock_KT-AA" + STR(COUNT_programmingBlock_KT) + "AA\n";
            programmingBlock_KT.push_back(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField72)) == StrLower(keyWordCodeInTheTranspiledLangEndRB)) {
            COUNT_programmingBlock_RB++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_RB-programmingBlock_RB-AA" + STR(COUNT_programmingBlock_RB) + "AA\n";
            programmingBlock_RB.push_back(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField72)) == StrLower(keyWordCodeInTheTranspiledLangEndNIM)) {
            COUNT_programmingBlock_NIM++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_NIM-programmingBlock_NIM-AA" + STR(COUNT_programmingBlock_NIM) + "AA\n";
            programmingBlock_NIM.push_back(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField72)) == StrLower(keyWordCodeInTheTranspiledLangEndAHK)) {
            COUNT_programmingBlock_AHK++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_AHK-programmingBlock_AHK-AA" + STR(COUNT_programmingBlock_AHK) + "AA\n";
            programmingBlock_AHK.push_back(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField72)) == StrLower(keyWordCodeInTheTranspiledLangEndSWIFT)) {
            COUNT_programmingBlock_SWIFT++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_SWIFT-programmingBlock_SWIFT-AA" + STR(COUNT_programmingBlock_SWIFT) + "AA\n";
            programmingBlock_SWIFT.push_back(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField72)) == StrLower(keyWordCodeInTheTranspiledLangEndDART)) {
            COUNT_programmingBlock_DART++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_DART-programmingBlock_DART-AA" + STR(COUNT_programmingBlock_DART) + "AA\n";
            programmingBlock_DART.push_back(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField72)) == StrLower(keyWordCodeInTheTranspiledLangEndTS)) {
            COUNT_programmingBlock_TS++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_TS-programmingBlock_TS-AA" + STR(COUNT_programmingBlock_TS) + "AA\n";
            programmingBlock_TS.push_back(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField72)) == StrLower(keyWordCodeInTheTranspiledLangEndGROOVY)) {
            COUNT_programmingBlock_GROOVY++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_GROOVY-programmingBlock_GROOVY-AA" + STR(COUNT_programmingBlock_GROOVY) + "AA\n";
            programmingBlock_GROOVY.push_back(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField72)) == StrLower(keyWordCodeInTheTranspiledLangEndHTVM)) {
            COUNT_programmingBlock_HTVM++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_HTVM-programmingBlock_HTVM-AA" + STR(COUNT_programmingBlock_HTVM) + "AA\n";
            programmingBlock_HTVM.push_back(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
        }
        else if (Trim(StrLower(A_LoopField72)) == StrLower(keyWordCodeInHTVMend)) {
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            COUNT_programmingBlock_HTVMsyntax++;
            holdTempDataProgrammingBlockThenPutInArr = StringTrimRight(holdTempDataProgrammingBlockThenPutInArr, 1);
            programmingBlocksTemp += "programmingBlock_HTVMsyntax-programmingBlock_HTVMsyntax-AA" + STR(COUNT_programmingBlock_HTVMsyntax) + "AA\n";
            programmingBlock_HTVMsyntax.push_back(holdTempDataProgrammingBlockThenPutInArr);
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 0;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        }
        else if (inProgarmmingBlock == 1) {
            holdTempDataProgrammingBlockThenPutInArr += A_LoopField72 + "\n";
        }
        else if (Trim(StrLower(A_LoopField72)) == StrLower(keyWordCodeInTheTranspiledLangStart)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField72)) == StrLower(keyWordCodeInTheTranspiledLangStartCPP)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField72)) == StrLower(keyWordCodeInTheTranspiledLangStartPY)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField72)) == StrLower(keyWordCodeInTheTranspiledLangStartJS)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField72)) == StrLower(keyWordCodeInTheTranspiledLangStartGO)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField72)) == StrLower(keyWordCodeInTheTranspiledLangStartLUA)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField72)) == StrLower(keyWordCodeInTheTranspiledLangStartCS)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField72)) == StrLower(keyWordCodeInTheTranspiledLangStartJAVA)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField72)) == StrLower(keyWordCodeInTheTranspiledLangStartKT)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField72)) == StrLower(keyWordCodeInTheTranspiledLangStartRB)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField72)) == StrLower(keyWordCodeInTheTranspiledLangStartNIM)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField72)) == StrLower(keyWordCodeInTheTranspiledLangStartAHK)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField72)) == StrLower(keyWordCodeInTheTranspiledLangStartSWIFT)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField72)) == StrLower(keyWordCodeInTheTranspiledLangStartDART)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField72)) == StrLower(keyWordCodeInTheTranspiledLangStartTS)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField72)) == StrLower(keyWordCodeInTheTranspiledLangStartGROOVY)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField72)) == StrLower(keyWordCodeInTheTranspiledLangStartHTVM)) {
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
        }
        else if (Trim(StrLower(A_LoopField72)) == StrLower(keyWordCodeInHTVMstart)) {
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            holdTempDataProgrammingBlockThenPutInArr = "";
            inProgarmmingBlock = 1;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        } else {
            programmingBlocksTemp += A_LoopField72 + "\n";
        }
    }
    code = StringTrimRight(programmingBlocksTemp, 1);
    //programmingBlock_InTheTranspiledLang
    //programmingBlock_CPP
    //programmingBlock_PY
    //programmingBlock_JS
    //programmingBlock_GO
    //programmingBlock_LUA
    //programmingBlock_CS
    //programmingBlock_JAVA
    //programmingBlock_KT
    //programmingBlock_RB
    //programmingBlock_NIM
    //programmingBlock_AHK
    //programmingBlock_SWIFT
    //programmingBlock_DART
    //programmingBlock_TS
    //programmingBlock_GROOVY
    //programmingBlock_HTVM
    //programmingBlock_HTVMsyntax
    // PROGRAMMING BLOCK
    // PROGRAMMING BLOCK
    // PROGRAMMING BLOCK
    // PROGRAMMING BLOCK
    std::vector<std::string> lookIntoTheNextLineForFuncWhitNoKeyWord;
    int didWeUseMainLabel = 0;
    std::string codeOutFixAndAddMainFunc = "";
    std::string htCodeOutFixEnd = "";
    int htCodeOutFixINT = 0;
    int htCodeOutFixINT2 = 0;
    std::string beforeKeywordForRemoveCommentsOnTheEndOfTheLine = "";
    std::string newStringOutCode = "";
    int posForRemoveCommentsOnTheEndOfTheLine = 0;
    std::string originalStringForRemoveCommentsOnTheEndOfTheLine = "";
    std::string OutFixDoubleQuotesInsideDoubleQuotes = "";
    int fixOutFixDoubleQuotesInsideDoubleQuotesFIXok = 0;
    std::string htCodeOUT754754 = "";
    int areWEinSome34sNum = 0;
    int theIdNumOfThe34 = 0;
    std::vector<std::string> theIdNumOfThe34theVar;
    std::string ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes = "";
    std::vector<std::string> getAllCharForTheFurtureSoIcanAddEscapeChar;
    int removeNexFixkeyWordEscpaeChar = 0;
    if (isNotHTVMfile == 0) {
        print("============programmingBlock_CPP==================");
        print("============programmingBlock_CPP==================");
        if (programmingBlock_CPP.size() > 0) {
            for (int A_Index73 = 0; A_Index73 < programmingBlock_CPP.size() + 0; A_Index73++) {
                print(programmingBlock_CPP[A_Index73]);
            }
        }
        print("============programmingBlock_CPP==================");
        print("============programmingBlock_CPP==================");
        std::vector<std::string> items74 = LoopParseFunc(code);
        for (size_t A_Index74 = 0; A_Index74 < items74.size() + 0; A_Index74++) {
            std::string A_LoopField74 = items74[A_Index74 - 0];
            theIdNumOfThe34theVar.push_back("");
            theIdNumOfThe34theVar.push_back("");
        }
        std::vector<std::string> items75 = LoopParseFunc(code);
        for (size_t A_Index75 = 0; A_Index75 < items75.size() + 0; A_Index75++) {
            std::string A_LoopField75 = items75[A_Index75 - 0];
            theIdNumOfThe34theVar[A_Index75] = theIdNumOfThe34theVar[A_Index75] + Chr(34);
            getAllCharForTheFurtureSoIcanAddEscapeChar.push_back(A_LoopField75);
        }
        getAllCharForTheFurtureSoIcanAddEscapeChar.push_back(" ");
        ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes = Chr(34) + "ihuiuusgfgesrheidFor--asdsas--theuhtuwaesphoutr" + Chr(34);
        std::vector<std::string> items76 = LoopParseFunc(code);
        for (size_t A_Index76 = 0; A_Index76 < items76.size() + 0; A_Index76++) {
            std::string A_LoopField76 = items76[A_Index76 - 0];
            if (A_LoopField76 == keyWordEscpaeChar && getAllCharForTheFurtureSoIcanAddEscapeChar[A_Index76 + 1] == Chr(34)) {
                fixOutFixDoubleQuotesInsideDoubleQuotesFIXok = 1;
                OutFixDoubleQuotesInsideDoubleQuotes += ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes;
            } else {
                if (fixOutFixDoubleQuotesInsideDoubleQuotesFIXok != 1) {
                    OutFixDoubleQuotesInsideDoubleQuotes += A_LoopField76;
                } else {
                    fixOutFixDoubleQuotesInsideDoubleQuotesFIXok = 0;
                }
            }
        }
        code = OutFixDoubleQuotesInsideDoubleQuotes;
        if (keyWordEscpaeChar != Chr(92) && langToConvertTo != langFileExtension_2) {
            code = StrReplace(code, Chr(92), Chr(92) + Chr(92));
        }
        if (keyWordEscpaeChar == Chr(92) && langToConvertTo != langFileExtension_2) {
            std::vector<std::string> items77 = LoopParseFunc(code);
            for (size_t A_Index77 = 0; A_Index77 < items77.size() + 0; A_Index77++) {
                std::string A_LoopField77 = items77[A_Index77 - 0];
                if (A_LoopField77 == Chr(34)) {
                    areWEinSome34sNum++;
                }
                if (areWEinSome34sNum == 1) {
                    if (A_LoopField77 != Chr(34)) {
                        if (A_LoopField77 == keyWordEscpaeChar && langToConvertTo != langFileExtension_2) {
                            theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + Chr(92);
                        } else {
                            theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + A_LoopField77;
                        }
                    } else {
                        theIdNumOfThe34++;
                        htCodeOUT754754 += "ihuiuuhuuhtheidFor--asdsas--theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(theIdNumOfThe34) + Chr(65) + Chr(65);
                    }
                }
                if (areWEinSome34sNum == 2 || areWEinSome34sNum == 0) {
                    if (A_LoopField77 != Chr(34)) {
                        htCodeOUT754754 += A_LoopField77;
                    }
                    areWEinSome34sNum = 0;
                }
            }
        } else {
            std::vector<std::string> items78 = LoopParseFunc(code);
            for (size_t A_Index78 = 0; A_Index78 < items78.size() + 0; A_Index78++) {
                std::string A_LoopField78 = items78[A_Index78 - 0];
                if (A_LoopField78 == Chr(34)) {
                    areWEinSome34sNum++;
                }
                if (areWEinSome34sNum == 1) {
                    if (A_LoopField78 != Chr(34)) {
                        if (A_LoopField78 == keyWordEscpaeChar && keyWordEscpaeChar == getAllCharForTheFurtureSoIcanAddEscapeChar[A_Index78 + 1] && langToConvertTo != langFileExtension_2) {
                            theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + keyWordEscpaeChar;
                            removeNexFixkeyWordEscpaeChar = 1;
                        }
                        else if (A_LoopField78 == keyWordEscpaeChar && langToConvertTo != langFileExtension_2) {
                            if (removeNexFixkeyWordEscpaeChar != 1) {
                                theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + Chr(92);
                            } else {
                                removeNexFixkeyWordEscpaeChar = 0;
                            }
                        } else {
                            theIdNumOfThe34theVar[theIdNumOfThe34] = theIdNumOfThe34theVar[theIdNumOfThe34] + A_LoopField78;
                        }
                    } else {
                        theIdNumOfThe34++;
                        htCodeOUT754754 += "ihuiuuhuuhtheidFor--asdsas--theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(theIdNumOfThe34) + Chr(65) + Chr(65);
                    }
                }
                if (areWEinSome34sNum == 2 || areWEinSome34sNum == 0) {
                    if (A_LoopField78 != Chr(34)) {
                        htCodeOUT754754 += A_LoopField78;
                    }
                    areWEinSome34sNum = 0;
                }
            }
        }
        code = htCodeOUT754754;
        for (int A_Index79 = 0; A_Index79 < theIdNumOfThe34 + 0; A_Index79++) {
            theIdNumOfThe34theVar[A_Index79] = theIdNumOfThe34theVar[A_Index79] + Chr(34);
        }
        theIdNumOfThe34theVar.push_back(Chr(34));
        code = StrReplace(code, Chr(13), "");
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        if (langToConvertTo == langFileExtension_2) {
            if (useSemicolon_2 == "on") {
                theSemicolon = ";";
            } else {
                theSemicolon = "";
            }
            if (usePythonicColonSyntax_2 == "off") {
                theColon = "";
            } else {
                theColon = ":";
            }
        } else {
            if (langToConvertTo != "py" && langToConvertTo != "nim" && langToConvertTo != "ahk" && langToConvertTo != "go" && langToConvertTo != "lua" && langToConvertTo != "kt" && langToConvertTo != "rb" && langToConvertTo != "swift" && langToConvertTo != "groovy" && useSemicolon == "off") {
                theSemicolon = ";";
            } else {
                theSemicolon = "";
            }
            if (langToConvertTo != "py" && langToConvertTo != "nim" && usePythonicColonSyntax == "off") {
                theColon = "";
            } else {
                theColon = ":";
            }
        }
        std::vector<std::string> items80 = LoopParseFunc(code, "\n", "\r");
        for (size_t A_Index80 = 0; A_Index80 < items80.size() + 0; A_Index80++) {
            std::string A_LoopField80 = items80[A_Index80 - 0];
            // Define the original string
            originalStringForRemoveCommentsOnTheEndOfTheLine = A_LoopField80;
            // Find the position of the keyword in the original string
            posForRemoveCommentsOnTheEndOfTheLine = InStr(originalStringForRemoveCommentsOnTheEndOfTheLine, " " + keyWordComment);
            if (SubStr(Trim(A_LoopField80), 1, StrLen(keyWordComment)) != keyWordComment) {
                if (posForRemoveCommentsOnTheEndOfTheLine > 0) {
                    beforeKeywordForRemoveCommentsOnTheEndOfTheLine = A_LoopField80;
                    // Construct the new string with everything before the keyword
                    newStringOutCode += beforeKeywordForRemoveCommentsOnTheEndOfTheLine + "\n";
                } else {
                    newStringOutCode += A_LoopField80 + "\n";
                }
            } else {
                newStringOutCode += A_LoopField80 + "\n";
            }
        }
        code = StringTrimRight(newStringOutCode, 1);
        //MsgBox, % code
        if (useCurlyBraces == "on") {
            if (keyWordCurlyBraceOpen != "{") {
                std::vector<std::string> items81 = LoopParseFunc(code, "\n", "\r");
                for (size_t A_Index81 = 0; A_Index81 < items81.size() + 0; A_Index81++) {
                    std::string A_LoopField81 = items81[A_Index81 - 0];
                    htCodeOutFixINT2 = 0;
                    if (isLineAconstruct(Trim(A_LoopField81)) == true || Trim(A_LoopField81) == keyWordCurlyBraceOpen) {
                        htCodeOutFixINT2 = 1;
                    }
                    htCodeOutFixINT = 0;
                    std::vector<std::string> items82 = LoopParseFunc(A_LoopField81, " ");
                    for (size_t A_Index82 = 0; A_Index82 < items82.size() + 0; A_Index82++) {
                        std::string A_LoopField82 = items82[A_Index82 - 0];
                        htCodeOutFixINT++;
                    }
                    htCodeOutFixINT--;
                    std::vector<std::string> items83 = LoopParseFunc(A_LoopField81, " ");
                    for (size_t A_Index83 = 0; A_Index83 < items83.size() + 0; A_Index83++) {
                        std::string A_LoopField83 = items83[A_Index83 - 0];
                        if (htCodeOutFixINT == A_Index83 && htCodeOutFixINT2 == 1) {
                            htCodeOutFixINT2 = 0;
                            htCodeOutFixEnd += HTVMmatchStrRrplace(A_LoopField83, keyWordCurlyBraceOpen, "{") + " ";
                        } else {
                            htCodeOutFixEnd += A_LoopField83 + " ";
                        }
                    }
                    htCodeOutFixEnd = StringTrimRight(htCodeOutFixEnd, 1);
                    htCodeOutFixEnd += "\n";
                }
                code = StringTrimRight(htCodeOutFixEnd, 1);
            }
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            htCodeOutFixEnd = "";
            if (keyWordCurlyBraceClose != "}") {
                std::vector<std::string> items84 = LoopParseFunc(code, "\n", "\r");
                for (size_t A_Index84 = 0; A_Index84 < items84.size() + 0; A_Index84++) {
                    std::string A_LoopField84 = items84[A_Index84 - 0];
                    htCodeOutFixINT2 = 0;
                    if (isLineAconstruct(Trim(A_LoopField84)) == true || Trim(A_LoopField84) == keyWordCurlyBraceClose) {
                        htCodeOutFixINT2 = 1;
                    }
                    std::vector<std::string> items85 = LoopParseFunc(A_LoopField84, " ");
                    for (size_t A_Index85 = 0; A_Index85 < items85.size() + 0; A_Index85++) {
                        std::string A_LoopField85 = items85[A_Index85 - 0];
                        if (htCodeOutFixINT2 == 1 || Trim(A_LoopField85) == keyWordCurlyBraceClose) {
                            htCodeOutFixINT2 = 0;
                            htCodeOutFixEnd += HTVMmatchStrRrplace(A_LoopField85, keyWordCurlyBraceClose, "}") + " ";
                        } else {
                            htCodeOutFixEnd += A_LoopField85 + " ";
                        }
                    }
                    htCodeOutFixEnd = StringTrimRight(htCodeOutFixEnd, 1);
                    htCodeOutFixEnd += "\n";
                }
                code = StringTrimRight(htCodeOutFixEnd, 1);
            }
        }
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        htCodeOutFixEnd = "";
        if (useEnd == "on") {
            std::vector<std::string> items86 = LoopParseFunc(code, "\n", "\r");
            for (size_t A_Index86 = 0; A_Index86 < items86.size() + 0; A_Index86++) {
                std::string A_LoopField86 = items86[A_Index86 - 0];
                if (StrLower(Trim(A_LoopField86)) == StrLower(keyWordEnd)) {
                    htCodeOutFixEnd += "}\n";
                }
                else if (SubStr(StrLower(Trim(A_LoopField86)), 1, StrLen(StrLower(keyWordIF))) == StrLower(keyWordIF) && isLineAconstruct(Trim(A_LoopField86)) == true) {
                    htCodeOutFixEnd += A_LoopField86 + "\n{\n";
                }
                else if (SubStr(StrLower(Trim(A_LoopField86)), 1, StrLen(StrLower(keyWordWhileLoop))) == StrLower(keyWordWhileLoop) && isLineAconstruct(Trim(A_LoopField86)) == true) {
                    htCodeOutFixEnd += A_LoopField86 + "\n{\n";
                }
                else if (SubStr(StrLower(Trim(A_LoopField86)), 1, StrLen(StrLower(keyWordElseIf))) == StrLower(keyWordElseIf) && isLineAconstruct(Trim(A_LoopField86)) == true) {
                    htCodeOutFixEnd += "\n}\n" + A_LoopField86 + "\n{\n";
                }
                else if (SubStr(StrLower(Trim(A_LoopField86)), 1, StrLen(StrLower(keyWordElse))) == StrLower(keyWordElse) && isLineAconstruct(Trim(A_LoopField86)) == true) {
                    htCodeOutFixEnd += "\n}\n" + A_LoopField86 + "\n{\n";
                }
                else if (SubStr(StrLower(Trim(A_LoopField86)), 1, StrLen(StrLower(keyWordCatch))) == StrLower(keyWordCatch) && isLineAconstruct(Trim(A_LoopField86)) == true) {
                    htCodeOutFixEnd += "\n}\n" + A_LoopField86 + "\n{\n";
                }
                else if (SubStr(StrLower(Trim(A_LoopField86)), 1, StrLen(StrLower(keyWordFinally))) == StrLower(keyWordFinally) && isLineAconstruct(Trim(A_LoopField86)) == true) {
                    htCodeOutFixEnd += "\n}\n" + A_LoopField86 + "\n{\n";
                }
                else if (isLineAconstruct(Trim(A_LoopField86)) == true) {
                    htCodeOutFixEnd += A_LoopField86 + "\n{\n";
                } else {
                    htCodeOutFixEnd += A_LoopField86 + "\n";
                }
            }
            code = StringTrimRight(htCodeOutFixEnd, 1);
        }
        if (usePythonicColonSyntax == "off") {
            if (useEnd == "off" && useCurlyBraces == "off") {
                htCodeOutFixEnd = "";
                std::vector<std::string> items87 = LoopParseFunc(code, "\n", "\r");
                for (size_t A_Index87 = 0; A_Index87 < items87.size() + 0; A_Index87++) {
                    std::string A_LoopField87 = items87[A_Index87 - 0];
                    if (isLineAconstruct(Trim(A_LoopField87)) == true) {
                        htCodeOutFixEnd += A_LoopField87 + ":\n";
                    } else {
                        htCodeOutFixEnd += A_LoopField87 + "\n";
                    }
                }
                code = StringTrimRight(htCodeOutFixEnd, 1);
            }
        }
        if (useCurlyBraces == "off" && useEnd == "off") {
            code = AddCurlyBraces(code);
        }
        outTrimCode = "";
        std::vector<std::string> items88 = LoopParseFunc(code, "\n", "\r");
        for (size_t A_Index88 = 0; A_Index88 < items88.size() + 0; A_Index88++) {
            std::string A_LoopField88 = items88[A_Index88 - 0];
            outTrimCode += Trim(A_LoopField88) + "\n";
        }
        code = StringTrimRight(outTrimCode, 1);
        // for converting c++ to js and py
        //code := StrReplace(code, "{}", "[]")
        std::string outCodeFixBraces = "";
        for (int A_Index89 = 0; A_Index89 < 2 + 0; A_Index89++) {
            outCodeFixBraces = "";
            std::vector<std::string> items90 = LoopParseFunc(code, "\n", "\r");
            for (size_t A_Index90 = 0; A_Index90 < items90.size() + 0; A_Index90++) {
                std::string A_LoopField90 = items90[A_Index90 - 0];
                if (InStr(Trim(A_LoopField90), "{") && Trim(A_LoopField90) != "{") {
                    outCodeFixBraces += Trim(StrReplace(Trim(A_LoopField90), "{", "")) + "\n{\n";
                }
                else if (InStr(Trim(A_LoopField90), "}") && Trim(A_LoopField90) != "}") {
                    outCodeFixBraces += "}\n" + Trim(StrReplace(Trim(A_LoopField90), "}", "")) + "\n";
                } else {
                    outCodeFixBraces += Trim(A_LoopField90) + "\n";
                }
            }
            code = StringTrimRight(outCodeFixBraces, 1);
        }
        htCodeOutFixEnd = "";
        if (usePythonicColonSyntax == "on") {
            std::vector<std::string> items91 = LoopParseFunc(code, "\n", "\r");
            for (size_t A_Index91 = 0; A_Index91 < items91.size() + 0; A_Index91++) {
                std::string A_LoopField91 = items91[A_Index91 - 0];
                if (isLineAconstruct(Trim(A_LoopField91)) == true) {
                    htCodeOutFixEnd += StringTrimRight(A_LoopField91, 1) + "\n";
                } else {
                    htCodeOutFixEnd += A_LoopField91 + "\n";
                }
            }
            code = StringTrimRight(htCodeOutFixEnd, 1);
        }
        //;; main loop ;;;
        //;; main loop ;;;
        //;; main loop ;;;
        //;; main loop ;;;
        fullLangAllOperators = GETfullLangAllOperators();
        fullLangAllOperators_HELP = GETfullLangAllOperators_HELP();
        if (isNotHTVMfile2 == 0) {
            std::vector<std::string> items92 = LoopParseFunc(code, "\n", "\r");
            for (size_t A_Index92 = 0; A_Index92 < items92.size() + 0; A_Index92++) {
                std::string A_LoopField92 = items92[A_Index92 - 0];
                if (StrLower(A_LoopField92) == StrLower(keyWordMainLabel)) {
                    didWeUseMainLabel = 1;
                    if (langToConvertTo == langFileExtension_2) {
                        codeOutFixAndAddMainFunc += keyWordMainLabel_2 + Chr(10);
                    }
                    if (langToConvertTo == "cpp") {
                        codeOutFixAndAddMainFunc += "int main(int argc, char* argv[])\n{\n";
                    }
                    if (langToConvertTo == "js" && useJavaScriptAmainFuncDef == "on") {
                        codeOutFixAndAddMainFunc += "async function main()\n{\n";
                    }
                    if (langToConvertTo == "ts" && useJavaScriptAmainFuncDef == "on") {
                        codeOutFixAndAddMainFunc += "async function main(): Promise<void>\n{\n";
                    }
                    if (langToConvertTo == "go") {
                        codeOutFixAndAddMainFunc += "func main()\n{\n";
                    }
                    if (langToConvertTo == "cs") {
                        codeOutFixAndAddMainFunc += "static void Main(string[] args)\n{\n";
                    }
                    if (langToConvertTo == "java") {
                        codeOutFixAndAddMainFunc += "public static void main(String[] args)\n{\n";
                    }
                    if (langToConvertTo == "kt") {
                        codeOutFixAndAddMainFunc += "fun main(args: Array<String>)\n{\n";
                    }
                    if (langToConvertTo == "swift") {
                        codeOutFixAndAddMainFunc += "func main()\n{\n";
                    }
                    if (langToConvertTo == "dart") {
                        codeOutFixAndAddMainFunc += "void main(List<String> arguments)\n{\n";
                    }
                } else {
                    codeOutFixAndAddMainFunc += A_LoopField92 + "\n";
                }
            }
            if (didWeUseMainLabel != 1 && langToConvertTo == "cpp") {
                codeOutFixAndAddMainFunc = "int main(int argc, char* argv[])\n{\n" + codeOutFixAndAddMainFunc;
            }
            if (didWeUseMainLabel != 1 && langToConvertTo == "js" && useJavaScriptAmainFuncDef == "on") {
                codeOutFixAndAddMainFunc = "async function main()\n{\n" + codeOutFixAndAddMainFunc;
            }
            if (didWeUseMainLabel != 1 && langToConvertTo == "ts" && useJavaScriptAmainFuncDef == "on") {
                codeOutFixAndAddMainFunc = "async function main(): Promise<void>\n{\n" + codeOutFixAndAddMainFunc;
            }
            if (didWeUseMainLabel != 1 && langToConvertTo == "go") {
                codeOutFixAndAddMainFunc = "func main()\n{\n" + codeOutFixAndAddMainFunc;
            }
            if (didWeUseMainLabel != 1 && langToConvertTo == "cs") {
                codeOutFixAndAddMainFunc = "static void Main(string[] args)\n{\n" + codeOutFixAndAddMainFunc;
            }
            if (didWeUseMainLabel != 1 && langToConvertTo == "java") {
                codeOutFixAndAddMainFunc = "public static void main(String[] args)\n{\n" + codeOutFixAndAddMainFunc;
            }
            if (didWeUseMainLabel != 1 && langToConvertTo == "kt") {
                codeOutFixAndAddMainFunc = "fun main(args: Array<String>)\n{\n" + codeOutFixAndAddMainFunc;
            }
            if (didWeUseMainLabel != 1 && langToConvertTo == "swift") {
                codeOutFixAndAddMainFunc = "func main()\n{\n" + codeOutFixAndAddMainFunc;
            }
            if (didWeUseMainLabel != 1 && langToConvertTo == "dart") {
                codeOutFixAndAddMainFunc = "void main(List<String> arguments)\n{\n" + codeOutFixAndAddMainFunc;
            }
            code = StringTrimRight(codeOutFixAndAddMainFunc, 1);
            // main loop
            // main loop
        }
        std::vector<std::string> items93 = LoopParseFunc(code, "\n", "\r");
        for (size_t A_Index93 = 0; A_Index93 < items93.size() + 0; A_Index93++) {
            std::string A_LoopField93 = items93[A_Index93 - 0];
            lookIntoTheNextLineForFuncWhitNoKeyWord.push_back(A_LoopField93);
        }
        lookIntoTheNextLineForFuncWhitNoKeyWord.push_back(" ");
        htCode = "";
        print("=======UP==========");
        print(code);
        print("=======DOWN==========");
        std::vector<std::string> items94 = LoopParseFunc(code, "\n", "\r");
        for (size_t A_Index94 = 0; A_Index94 < items94.size() + 0; A_Index94++) {
            std::string A_LoopField94 = items94[A_Index94 - 0];
            lineDone = 0;
            if (SubStr(A_LoopField94, 1, StrLen(keyWordComment)) == keyWordComment) {
                str1 = StringTrimLeft(A_LoopField94, StrLen(keyWordComment));
                if (langToConvertTo == langFileExtension_2) {
                    htCode += keyWordComment_2 + str1 + Chr(10);
                }
                if (langToConvertTo == "cpp") {
                    htCode += "//" + str1 + Chr(10);
                }
                if (langToConvertTo == "py") {
                    htCode += "#" + str1 + Chr(10);
                }
                if (langToConvertTo == "js") {
                    htCode += "//" + str1 + Chr(10);
                }
                if (langToConvertTo == "go") {
                    htCode += "//" + str1 + Chr(10);
                }
                if (langToConvertTo == "lua") {
                    htCode += "--" + str1 + Chr(10);
                }
                if (langToConvertTo == "cs") {
                    htCode += "//" + str1 + Chr(10);
                }
                if (langToConvertTo == "java") {
                    htCode += "//" + str1 + Chr(10);
                }
                if (langToConvertTo == "kt") {
                    htCode += "//" + str1 + Chr(10);
                }
                if (langToConvertTo == "rb") {
                    htCode += "#" + str1 + Chr(10);
                }
                if (langToConvertTo == "nim") {
                    htCode += "#" + str1 + Chr(10);
                }
                if (langToConvertTo == "ahk") {
                    htCode += ";" + str1 + Chr(10);
                }
                if (langToConvertTo == "swift") {
                    htCode += "//" + str1 + Chr(10);
                }
                if (langToConvertTo == "dart") {
                    htCode += "//" + str1 + Chr(10);
                }
                if (langToConvertTo == "ts") {
                    htCode += "//" + str1 + Chr(10);
                }
                if (langToConvertTo == "groovy") {
                    htCode += "//" + str1 + Chr(10);
                }
            }
            else if (Trim(A_LoopField94) == keyWordCommentOpenMultiLine) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode += keyWordCommentOpenMultiLine_2 + Chr(10);
                }
                if (langToConvertTo == "cpp") {
                    htCode += "/*" + Chr(10);
                }
                if (langToConvertTo == "py") {
                    htCode += Chr(34) + Chr(34) + Chr(34) + Chr(10);
                }
                if (langToConvertTo == "js") {
                    htCode += "/*" + Chr(10);
                }
                if (langToConvertTo == "go") {
                    htCode += "/*" + Chr(10);
                }
                if (langToConvertTo == "lua") {
                    htCode += "--[[" + Chr(10);
                }
                if (langToConvertTo == "cs") {
                    htCode += "/*" + Chr(10);
                }
                if (langToConvertTo == "java") {
                    htCode += "/*" + Chr(10);
                }
                if (langToConvertTo == "kt") {
                    htCode += "/*" + Chr(10);
                }
                if (langToConvertTo == "rb") {
                    htCode += "=begin" + Chr(10);
                }
                if (langToConvertTo == "nim") {
                    htCode += "#[" + Chr(10);
                }
                if (langToConvertTo == "ahk") {
                    htCode += "/*" + Chr(10);
                }
                if (langToConvertTo == "swift") {
                    htCode += "/*" + Chr(10);
                }
                if (langToConvertTo == "dart") {
                    htCode += "/*" + Chr(10);
                }
                if (langToConvertTo == "ts") {
                    htCode += "/*" + Chr(10);
                }
                if (langToConvertTo == "groovy") {
                    htCode += "/*" + Chr(10);
                }
            }
            else if (Trim(A_LoopField94) == keyWordCommentCloseMultiLine) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode += keyWordCommentCloseMultiLine_2 + Chr(10);
                }
                if (langToConvertTo == "cpp") {
                    htCode += "*/" + Chr(10);
                }
                if (langToConvertTo == "py") {
                    htCode += Chr(34) + Chr(34) + Chr(34) + Chr(10);
                }
                if (langToConvertTo == "js") {
                    htCode += "*/" + Chr(10);
                }
                if (langToConvertTo == "go") {
                    htCode += "*/" + Chr(10);
                }
                if (langToConvertTo == "lua") {
                    htCode += "]]" + Chr(10);
                }
                if (langToConvertTo == "cs") {
                    htCode += "*/" + Chr(10);
                }
                if (langToConvertTo == "java") {
                    htCode += "*/" + Chr(10);
                }
                if (langToConvertTo == "kt") {
                    htCode += "*/" + Chr(10);
                }
                if (langToConvertTo == "rb") {
                    htCode += "=end" + Chr(10);
                }
                if (langToConvertTo == "nim") {
                    htCode += "]#" + Chr(10);
                }
                if (langToConvertTo == "ahk") {
                    htCode += "*/" + Chr(10);
                }
                if (langToConvertTo == "swift") {
                    htCode += "*/" + Chr(10);
                }
                if (langToConvertTo == "dart") {
                    htCode += "*/" + Chr(10);
                }
                if (langToConvertTo == "ts") {
                    htCode += "*/" + Chr(10);
                }
                if (langToConvertTo == "groovy") {
                    htCode += "*/" + Chr(10);
                }
            }
            else if (SubStr(StrLower(Trim(A_LoopField94)), 1, StrLen(StrLower(keyWordIF))) == StrLower(keyWordIF)) {
                str1 = Trim(StringTrimLeft(A_LoopField94, StrLen(keyWordIF)));
                str1 = Trim(expressionParserTranspiler("(" + str1 + ")"));
                str1 = StringTrimRight(str1, 1);
                str1 = StringTrimLeft(str1, 1);
                if (langToConvertTo == langFileExtension_2) {
                    if (usePythonicColonSyntax_2 == "on") {
                        if (useParentheses == "on") {
                            if (useParentheses_2 == "on") {
                                htCode += keyWordIF_2 + str1 + ":\n";
                            } else {
                                htCode += keyWordIF_2 + StringTrimRight(StringTrimLeft(Trim(str1), 1), 1) + ":\n";
                            }
                        } else {
                            if (useParentheses_2 == "on") {
                                htCode += keyWordIF_2 + "(" + str1 + "):\n";
                            } else {
                                htCode += keyWordIF_2 + str1 + ":\n";
                            }
                        }
                    } else {
                        if (useParentheses == "on") {
                            if (useParentheses_2 == "on") {
                                htCode += keyWordIF_2 + str1 + "\n";
                            } else {
                                htCode += keyWordIF_2 + StringTrimRight(StringTrimLeft(Trim(str1), 1), 1) + "\n";
                            }
                        } else {
                            if (useParentheses_2 == "on") {
                                htCode += keyWordIF_2 + "(" + str1 + ")\n";
                            } else {
                                htCode += keyWordIF_2 + str1 + "\n";
                            }
                        }
                    }
                }
                if (langToConvertTo == "cpp") {
                    if (useParentheses == "on") {
                        htCode += "if " + str1 + Chr(10);
                    } else {
                        htCode += "if (" + str1 + ")" + Chr(10);
                    }
                }
                if (langToConvertTo == "py") {
                    htCode += "if " + str1 + ":" + Chr(10);
                }
                if (langToConvertTo == "js") {
                    if (useParentheses == "on") {
                        htCode += "if " + str1 + Chr(10);
                    } else {
                        htCode += "if (" + str1 + ")" + Chr(10);
                    }
                }
                if (langToConvertTo == "go") {
                    htCode += "if " + str1 + "\n";
                }
                if (langToConvertTo == "lua") {
                    htCode += "if " + str1 + " then\n";
                }
                if (langToConvertTo == "cs") {
                    if (useParentheses == "on") {
                        htCode += "if " + str1 + "\n";
                    } else {
                        htCode += "if (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "java") {
                    if (useParentheses == "on") {
                        htCode += "if " + str1 + "\n";
                    } else {
                        htCode += "if (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "kt") {
                    if (useParentheses == "on") {
                        htCode += "if " + str1 + "\n";
                    } else {
                        htCode += "if (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "rb") {
                    htCode += "if " + str1 + "\n";
                }
                if (langToConvertTo == "nim") {
                    htCode += "if " + str1 + ":\n";
                }
                if (langToConvertTo == "ahk") {
                    if (useParentheses == "on") {
                        htCode += "if " + str1 + "\n";
                    } else {
                        htCode += "if (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "swift") {
                    htCode += "if " + str1 + "\n";
                }
                if (langToConvertTo == "dart") {
                    if (useParentheses == "on") {
                        htCode += "if " + str1 + "\n";
                    } else {
                        htCode += "if (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "ts") {
                    if (useParentheses == "on") {
                        htCode += "if " + str1 + "\n";
                    } else {
                        htCode += "if (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "groovy") {
                    htCode += "if " + str1 + "\n";
                }
            }
            else if (SubStr(StrLower(Trim(A_LoopField94)), 1, StrLen(StrLower(keyWordElseIf))) == StrLower(keyWordElseIf)) {
                str1 = Trim(StringTrimLeft(A_LoopField94, StrLen(keyWordElseIf)));
                str1 = Trim(expressionParserTranspiler("(" + str1 + ")"));
                str1 = StringTrimRight(str1, 1);
                str1 = StringTrimLeft(str1, 1);
                if (langToConvertTo == langFileExtension_2) {
                    if (usePythonicColonSyntax_2 == "on") {
                        if (useParentheses == "on") {
                            if (useParentheses_2 == "on") {
                                htCode += keyWordElseIf_2 + str1 + ":\n";
                            } else {
                                htCode += keyWordElseIf_2 + StringTrimRight(StringTrimLeft(Trim(str1), 1), 1) + ":\n";
                            }
                        } else {
                            if (useParentheses_2 == "on") {
                                htCode += keyWordElseIf_2 + "(" + str1 + "):\n";
                            } else {
                                htCode += keyWordElseIf_2 + str1 + ":\n";
                            }
                        }
                    } else {
                        if (useParentheses == "on") {
                            if (useParentheses_2 == "on") {
                                htCode += keyWordElseIf_2 + str1 + "\n";
                            } else {
                                htCode += keyWordElseIf_2 + StringTrimRight(StringTrimLeft(Trim(str1), 1), 1) + "\n";
                            }
                        } else {
                            if (useParentheses_2 == "on") {
                                htCode += keyWordElseIf_2 + "(" + str1 + ")\n";
                            } else {
                                htCode += keyWordElseIf_2 + str1 + "\n";
                            }
                        }
                    }
                }
                if (langToConvertTo == "cpp") {
                    if (useParentheses == "on") {
                        htCode += "else if " + str1 + "\n";
                    } else {
                        htCode += "else if (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "py") {
                    htCode += "elif " + str1 + ":\n";
                }
                if (langToConvertTo == "js") {
                    if (useParentheses == "on") {
                        htCode += "else if " + str1 + "\n";
                    } else {
                        htCode += "else if (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "go") {
                    htCode += "else if " + str1 + "\n";
                }
                if (langToConvertTo == "lua") {
                    htCode += "elseif " + str1 + " then\n";
                }
                if (langToConvertTo == "cs") {
                    if (useParentheses == "on") {
                        htCode += "else if " + str1 + "\n";
                    } else {
                        htCode += "else if (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "java") {
                    if (useParentheses == "on") {
                        htCode += "else if " + str1 + "\n";
                    } else {
                        htCode += "else if (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "kt") {
                    if (useParentheses == "on") {
                        htCode += "else if " + str1 + "\n";
                    } else {
                        htCode += "else if (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "rb") {
                    htCode += "elsif " + str1 + "\n";
                }
                if (langToConvertTo == "nim") {
                    htCode += "elif " + str1 + ":\n";
                }
                if (langToConvertTo == "ahk") {
                    if (useParentheses == "on") {
                        htCode += "else if " + str1 + "\n";
                    } else {
                        htCode += "else if (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "swift") {
                    htCode += "else if " + str1 + "\n";
                }
                if (langToConvertTo == "dart") {
                    if (useParentheses == "on") {
                        htCode += "else if " + str1 + "\n";
                    } else {
                        htCode += "else if (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "ts") {
                    if (useParentheses == "on") {
                        htCode += "else if " + str1 + "\n";
                    } else {
                        htCode += "else if (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "groovy") {
                    htCode += "else if " + str1 + "\n";
                }
            }
            else if (StrLower(Trim(A_LoopField94)) == StrLower(keyWordElse) || StrLower(Trim(A_LoopField94)) == StrLower(keyWordElse + ":")) {
                if (langToConvertTo == langFileExtension_2) {
                    if (usePythonicColonSyntax_2 == "on") {
                        htCode += keyWordElse_2 + ":\n";
                    } else {
                        htCode += keyWordElse_2 + "\n";
                    }
                }
                if (langToConvertTo == "cpp") {
                    htCode += "else\n";
                }
                if (langToConvertTo == "py") {
                    htCode += "else:\n";
                }
                if (langToConvertTo == "js") {
                    htCode += "else\n";
                }
                if (langToConvertTo == "go") {
                    htCode += "else\n";
                }
                if (langToConvertTo == "lua") {
                    htCode += "else\n";
                }
                if (langToConvertTo == "cs") {
                    htCode += "else\n";
                }
                if (langToConvertTo == "java") {
                    htCode += "else\n";
                }
                if (langToConvertTo == "kt") {
                    htCode += "else\n";
                }
                if (langToConvertTo == "rb") {
                    htCode += "else\n";
                }
                if (langToConvertTo == "nim") {
                    htCode += "else:\n";
                }
                if (langToConvertTo == "ahk") {
                    htCode += "else\n";
                }
                if (langToConvertTo == "swift") {
                    htCode += "else\n";
                }
                if (langToConvertTo == "dart") {
                    htCode += "else\n";
                }
                if (langToConvertTo == "ts") {
                    htCode += "else\n";
                }
                if (langToConvertTo == "groovy") {
                    htCode += "else\n";
                }
            }
            else if (SubStr(StrLower(Trim(A_LoopField94)), 1, StrLen(StrLower(keyWordWhileLoop))) == StrLower(keyWordWhileLoop)) {
                str1 = Trim(StringTrimLeft(A_LoopField94, StrLen(keyWordWhileLoop)));
                str1 = Trim(expressionParserTranspiler("(" + str1 + ")"));
                str1 = StringTrimRight(str1, 1);
                str1 = StringTrimLeft(str1, 1);
                if (langToConvertTo == langFileExtension_2) {
                    if (usePythonicColonSyntax_2 == "on") {
                        if (useParentheses == "on") {
                            if (useParentheses_2 == "on") {
                                htCode += keyWordWhileLoop_2 + str1 + ":" + Chr(10);
                            } else {
                                htCode += keyWordWhileLoop_2 + StringTrimRight(StringTrimLeft(Trim(str1), 1), 1) + ":" + Chr(10);
                            }
                        } else {
                            if (useParentheses_2 == "on") {
                                htCode += keyWordWhileLoop_2 + "(" + str1 + "):" + Chr(10);
                            } else {
                                htCode += keyWordWhileLoop_2 + str1 + ":" + Chr(10);
                            }
                        }
                    } else {
                        if (useParentheses == "on") {
                            if (useParentheses_2 == "on") {
                                htCode += keyWordWhileLoop_2 + str1 + Chr(10);
                            } else {
                                htCode += keyWordWhileLoop_2 + StringTrimRight(StringTrimLeft(Trim(str1), 1), 1) + Chr(10);
                            }
                        } else {
                            if (useParentheses_2 == "on") {
                                htCode += keyWordWhileLoop_2 + "(" + str1 + ")" + Chr(10);
                            } else {
                                htCode += keyWordWhileLoop_2 + str1 + Chr(10);
                            }
                        }
                    }
                }
                if (langToConvertTo == "cpp") {
                    if (useParentheses == "on") {
                        htCode += "while " + str1 + Chr(10);
                    } else {
                        htCode += "while (" + str1 + ")" + Chr(10);
                    }
                }
                if (langToConvertTo == "py") {
                    htCode += "while " + str1 + ":" + Chr(10);
                }
                if (langToConvertTo == "js") {
                    if (useParentheses == "on") {
                        htCode += "while " + str1 + Chr(10);
                    } else {
                        htCode += "while (" + str1 + ")" + Chr(10);
                    }
                }
                if (langToConvertTo == "go") {
                    htCode += "for " + str1 + Chr(10);
                }
                if (langToConvertTo == "lua") {
                    htCode += "while " + str1 + " do" + Chr(10);
                }
                if (langToConvertTo == "cs") {
                    if (useParentheses == "on") {
                        htCode += "while " + str1 + Chr(10);
                    } else {
                        htCode += "while (" + str1 + ")" + Chr(10);
                    }
                }
                if (langToConvertTo == "java") {
                    if (useParentheses == "on") {
                        htCode += "while " + str1 + Chr(10);
                    } else {
                        htCode += "while (" + str1 + ")" + Chr(10);
                    }
                }
                if (langToConvertTo == "kt") {
                    if (useParentheses == "on") {
                        htCode += "while " + str1 + "\n";
                    } else {
                        htCode += "while (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "rb") {
                    htCode += "while " + str1 + "\n";
                }
                if (langToConvertTo == "nim") {
                    htCode += "while " + str1 + ":\n";
                }
                if (langToConvertTo == "ahk") {
                    if (useParentheses == "on") {
                        htCode += "while " + str1 + "\n";
                    } else {
                        htCode += "while (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "swift") {
                    htCode += "while " + str1 + "\n";
                }
                if (langToConvertTo == "dart") {
                    if (useParentheses == "on") {
                        htCode += "while " + str1 + "\n";
                    } else {
                        htCode += "while (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "ts") {
                    if (useParentheses == "on") {
                        htCode += "while " + str1 + "\n";
                    } else {
                        htCode += "while (" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "groovy") {
                    htCode += "while " + str1 + "\n";
                }
            }
            else if (StrLower(Trim(A_LoopField94)) == StrLower(keyWordTry) || StrLower(Trim(A_LoopField94)) == StrLower(keyWordTry + ":")) {
                if (langToConvertTo == langFileExtension_2) {
                    if (usePythonicColonSyntax_2 == "on") {
                        htCode += keyWordTry_2 + ":\n";
                    } else {
                        htCode += keyWordTry_2 + "\n";
                    }
                }
                if (langToConvertTo == "cpp") {
                    htCode += "try\n";
                }
                if (langToConvertTo == "py") {
                    htCode += "try:\n";
                }
                if (langToConvertTo == "js") {
                    htCode += "try\n";
                }
                if (langToConvertTo == "go") {
                    htCode += "GO DOSENT HAVE A TRY USE PROGRAMMING BLOCKS MAYBE IDK\n";
                }
                if (langToConvertTo == "lua") {
                    htCode += "LUA DOSENT HAVE A TRY USE PROGRAMMING BLOCKS MAYBE IDK\n";
                }
                if (langToConvertTo == "cs") {
                    htCode += "try\n";
                }
                if (langToConvertTo == "java") {
                    htCode += "try\n";
                }
                if (langToConvertTo == "kt") {
                    htCode += "try\n";
                }
                if (langToConvertTo == "rb") {
                    htCode += "begin\n";
                }
                if (langToConvertTo == "nim") {
                    htCode += "try:\n";
                }
                if (langToConvertTo == "ahk") {
                    htCode += "try\n";
                }
                if (langToConvertTo == "swift") {
                    htCode += "do\n";
                }
                if (langToConvertTo == "dart") {
                    htCode += "try\n";
                }
                if (langToConvertTo == "ts") {
                    htCode += "try\n";
                }
                if (langToConvertTo == "groovy") {
                    htCode += "try\n";
                }
            }
            else if (SubStr(StrLower(Trim(A_LoopField94)), 1, StrLen(StrLower(keyWordCatch))) == StrLower(keyWordCatch)) {
                str1 = Trim(StrReplace(StrReplace(StringTrimLeft(A_LoopField94, StrLen(keyWordCatch)), "(", ""), ")", ""));
                theTryCatchVarForErrors = str1;
                if (langToConvertTo == langFileExtension_2) {
                    if (usePythonicColonSyntax_2 == "on") {
                        htCode += keyWordCatch_2 + "(" + str1 + "):\n";
                    } else {
                        htCode += keyWordCatch_2 + "(" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "cpp") {
                    htCode += "catch (const std::exception& " + str1 + ")\n";
                }
                if (langToConvertTo == "py") {
                    htCode += "except Exception as " + str1 + ":\n";
                }
                if (langToConvertTo == "js") {
                    htCode += "catch (" + str1 + ")\n";
                }
                if (langToConvertTo == "go") {
                    htCode += "GO DOSENT HAVE A CATCH USE PROGRAMMING BLOCKS MAYBE IDK\n";
                }
                if (langToConvertTo == "lua") {
                    htCode += "LUA DOSENT HAVE A CATCH USE PROGRAMMING BLOCKS MAYBE IDK\n";
                }
                if (langToConvertTo == "cs") {
                    htCode += "catch (Exception " + str1 + ")\n";
                }
                if (langToConvertTo == "java") {
                    htCode += "catch (Exception " + str1 + ")\n";
                }
                if (langToConvertTo == "kt") {
                    htCode += "catch (" + str1 + ": Exception)\n";
                }
                if (langToConvertTo == "rb") {
                    htCode += "rescue => " + str1 + "\n";
                }
                if (langToConvertTo == "nim") {
                    htCode += "except ValueError as " + str1 + ":\n";
                }
                if (langToConvertTo == "ahk") {
                    htCode += "catch " + str1 + "\n";
                }
                if (langToConvertTo == "swift") {
                    htCode += "catch let " + str1 + " as NSError\n";
                }
                if (langToConvertTo == "dart") {
                    htCode += "catch (" + str1 + ")\n";
                }
                if (langToConvertTo == "ts") {
                    htCode += "catch (" + str1 + ")\n";
                }
                if (langToConvertTo == "groovy") {
                    htCode += "catch (Exception " + str1 + ")\n";
                }
            }
            else if (StrLower(Trim(A_LoopField94)) == StrLower(keyWordFinally) || StrLower(Trim(A_LoopField94)) == StrLower(keyWordFinally + ":")) {
                if (langToConvertTo == langFileExtension_2) {
                    if (usePythonicColonSyntax_2 == "on") {
                        htCode += keyWordFinally_2 + ":\n";
                    } else {
                        htCode += keyWordFinally_2 + "\n";
                    }
                }
                if (langToConvertTo == "cpp") {
                    htCode += "if (" + Chr(34) + "finally dosent exist in c++" + Chr(34) + " == " + Chr(34) + "finally dosent exist in c++" + Chr(34) + ")\n";
                }
                if (langToConvertTo == "py") {
                    htCode += "finally:\n";
                }
                if (langToConvertTo == "js") {
                    htCode += "finally\n";
                }
                if (langToConvertTo == "go") {
                    htCode += "GO DOSENT HAVE A FINALLY USE PROGRAMMING BLOCKS MAYBE IDK\n";
                }
                if (langToConvertTo == "lua") {
                    htCode += "LUA DOSENT HAVE A FINALLY USE PROGRAMMING BLOCKS MAYBE IDK\n";
                }
                if (langToConvertTo == "cs") {
                    htCode += "finally\n";
                }
                if (langToConvertTo == "java") {
                    htCode += "finally\n";
                }
                if (langToConvertTo == "kt") {
                    htCode += "finally\n";
                }
                if (langToConvertTo == "rb") {
                    htCode += "ensure\n";
                }
                if (langToConvertTo == "nim") {
                    htCode += "finally:\n";
                }
                if (langToConvertTo == "ahk") {
                    htCode += "finally\n";
                }
                if (langToConvertTo == "swift") {
                    htCode += "if (" + Chr(34) + "finally dosent exist in swift" + Chr(34) + " == " + Chr(34) + "finally dosent exist in swift" + Chr(34) + ")\n";
                }
                if (langToConvertTo == "dart") {
                    htCode += "finally\n";
                }
                if (langToConvertTo == "ts") {
                    htCode += "finally\n";
                }
                if (langToConvertTo == "groovy") {
                    htCode += "finally\n";
                }
            }
            else if (SubStr(StrLower(Trim(A_LoopField94)), 1, StrLen(StrLower(keyWordThrow))) == StrLower(keyWordThrow)) {
                str1 = expressionParserTranspiler(fixArray1234(Trim(StringTrimLeft(A_LoopField94, StrLen(keyWordThrow)))));
                if (langToConvertTo == langFileExtension_2) {
                    if (useSemicolon_2 == "on") {
                        htCode += keyWordThrow_2 + " " + keyWordErrorMsg + "(" + str1 + ");\n";
                    } else {
                        htCode += keyWordThrow_2 + " " + keyWordErrorMsg + "(" + str1 + ")\n";
                    }
                }
                if (langToConvertTo == "cpp") {
                    htCode += "throw std::runtime_error(" + str1 + ");\n";
                }
                if (langToConvertTo == "py") {
                    htCode += "raise Exception(" + str1 + ")\n";
                }
                if (langToConvertTo == "js") {
                    htCode += "throw new Error(" + str1 + ");\n";
                }
                if (langToConvertTo == "go") {
                    htCode += "GO DOSENT HAVE A THROW USE PROGRAMMING BLOCKS MAYBE IDK\n";
                }
                if (langToConvertTo == "lua") {
                    htCode += "LUA DOSENT HAVE A THROW USE PROGRAMMING BLOCKS MAYBE IDK\n";
                }
                if (langToConvertTo == "cs") {
                    htCode += "throw new Exception(" + str1 + ");\n";
                }
                if (langToConvertTo == "java") {
                    htCode += "throw new Exception(" + str1 + ");\n";
                }
                if (langToConvertTo == "kt") {
                    htCode += "throw Exception(" + str1 + ")" + Chr(10);
                }
                if (langToConvertTo == "rb") {
                    htCode += "raise " + str1 + Chr(10);
                }
                if (langToConvertTo == "nim") {
                    htCode += "raise newException(ValueError, " + str1 + ")\n";
                }
                if (langToConvertTo == "ahk") {
                    htCode += "throw " + str1 + "\n";
                }
                if (langToConvertTo == "swift") {
                    htCode += "try ErrorMsg(" + str1 + ")\n";
                }
                if (langToConvertTo == "dart") {
                    htCode += "throw Exception(" + str1 + ");\n";
                }
                if (langToConvertTo == "ts") {
                    htCode += " throw new Error(" + str1 + ");\n";
                }
                if (langToConvertTo == "groovy") {
                    htCode += "throw new Exception(" + str1 + ")\n";
                }
            }
            else if (StrLower(A_LoopField94) == StrLower(keyWordBreak) || StrLower(A_LoopField94) == StrLower(keyWordBreak + ";")) {
                if (langToConvertTo == langFileExtension_2) {
                    if (useSemicolon_2 == "on") {
                        htCode += keyWordBreak_2 + ";\n";
                    } else {
                        htCode += keyWordBreak_2 + "\n";
                    }
                }
                if (langToConvertTo == "cpp") {
                    htCode += "break;\n";
                }
                if (langToConvertTo == "py") {
                    htCode += "break\n";
                }
                if (langToConvertTo == "js") {
                    htCode += "break;\n";
                }
                if (langToConvertTo == "go") {
                    htCode += "break\n";
                }
                if (langToConvertTo == "lua") {
                    htCode += "break\n";
                }
                if (langToConvertTo == "cs") {
                    htCode += "break;\n";
                }
                if (langToConvertTo == "java") {
                    htCode += "break;\n";
                }
                if (langToConvertTo == "kt") {
                    htCode += "break\n";
                }
                if (langToConvertTo == "rb") {
                    htCode += "break\n";
                }
                if (langToConvertTo == "nim") {
                    htCode += "break\n";
                }
                if (langToConvertTo == "ahk") {
                    htCode += "break\n";
                }
                if (langToConvertTo == "swift") {
                    htCode += "break\n";
                }
                if (langToConvertTo == "dart") {
                    htCode += "break;\n";
                }
                if (langToConvertTo == "ts") {
                    htCode += "break;\n";
                }
                if (langToConvertTo == "groovy") {
                    htCode += "break;\n";
                }
            }
            else if (StrLower(A_LoopField94) == StrLower(Trim(keyWordReturnStatement)) || StrLower(A_LoopField94) == StrLower(Trim(keyWordReturnStatement) + ";")) {
                if (langToConvertTo == langFileExtension_2) {
                    if (useSemicolon_2 == "on") {
                        htCode += keyWordReturnStatement_2 + ";\n";
                    } else {
                        htCode += keyWordReturnStatement_2 + "\n";
                    }
                }
                if (langToConvertTo == "cpp") {
                    htCode += "return;\n";
                }
                if (langToConvertTo == "py") {
                    htCode += "return\n";
                }
                if (langToConvertTo == "js") {
                    htCode += "return;\n";
                }
                if (langToConvertTo == "go") {
                    htCode += "break\n";
                }
                if (langToConvertTo == "lua") {
                    htCode += "return\n";
                }
                if (langToConvertTo == "cs") {
                    htCode += "return;\n";
                }
                if (langToConvertTo == "java") {
                    htCode += "return;\n";
                }
                if (langToConvertTo == "kt") {
                    htCode += "return\n";
                }
                if (langToConvertTo == "rb") {
                    htCode += "return\n";
                }
                if (langToConvertTo == "nim") {
                    htCode += "return\n";
                }
                if (langToConvertTo == "ahk") {
                    htCode += "return\n";
                }
                if (langToConvertTo == "swift") {
                    htCode += "return\n";
                }
                if (langToConvertTo == "dart") {
                    htCode += "return;\n";
                }
                if (langToConvertTo == "ts") {
                    htCode += "return;\n";
                }
                if (langToConvertTo == "groovy") {
                    htCode += "return;\n";
                }
            }
            else if (SubStr(Trim(StrLower(A_LoopField94)), 1, StrLen(StrLower(keyWordReturnStatement))) == StrLower(keyWordReturnStatement)) {
                str1 = Trim(expressionParserTranspiler(Trim(StringTrimLeft(A_LoopField94, StrLen(keyWordReturnStatement)))));
                if (langToConvertTo == langFileExtension_2) {
                    if (useSemicolon_2 == "on") {
                        htCode += keyWordReturnStatement_2 + str1 + ";\n";
                    } else {
                        htCode += keyWordReturnStatement_2 + str1 + "\n";
                    }
                }
                if (langToConvertTo == "cpp") {
                    htCode += "return " + str1 + ";\n";
                }
                if (langToConvertTo == "py") {
                    htCode += "return " + str1 + "\n";
                }
                if (langToConvertTo == "js") {
                    htCode += "return " + str1 + ";\n";
                }
                if (langToConvertTo == "go") {
                    htCode += "return " + str1 + "\n";
                }
                if (langToConvertTo == "lua") {
                    htCode += "return " + str1 + "\n";
                }
                if (langToConvertTo == "cs") {
                    htCode += "return " + str1 + ";\n";
                }
                if (langToConvertTo == "java") {
                    htCode += "return " + str1 + ";\n";
                }
                if (langToConvertTo == "kt") {
                    htCode += "return " + str1 + "\n";
                }
                if (langToConvertTo == "rb") {
                    htCode += "return " + str1 + "\n";
                }
                if (langToConvertTo == "nim") {
                    htCode += "return " + str1 + "\n";
                }
                if (langToConvertTo == "ahk") {
                    htCode += "return " + str1 + "\n";
                }
                if (langToConvertTo == "swift") {
                    htCode += "return " + str1 + "\n";
                }
                if (langToConvertTo == "dart") {
                    htCode += "return " + str1 + ";\n";
                }
                if (langToConvertTo == "ts") {
                    htCode += "return " + str1 + ";\n";
                }
                if (langToConvertTo == "groovy") {
                    htCode += "return " + str1 + ";\n";
                }
            }
            else if (StrLower(A_LoopField94) == StrLower(keyWordContinue) || StrLower(A_LoopField94) == StrLower(keyWordContinue + ";")) {
                if (langToConvertTo == langFileExtension_2) {
                    if (useSemicolon_2 == "on") {
                        htCode += keyWordContinue_2 + ";\n";
                    } else {
                        htCode += keyWordContinue_2 + "\n";
                    }
                }
                if (langToConvertTo == "cpp") {
                    htCode += "continue;\n";
                }
                if (langToConvertTo == "py") {
                    htCode += "continue\n";
                }
                if (langToConvertTo == "js") {
                    htCode += "continue;\n";
                }
                if (langToConvertTo == "go") {
                    htCode += "continue\n";
                }
                if (langToConvertTo == "lua") {
                    htCode += "goto continue\n";
                }
                if (langToConvertTo == "cs") {
                    htCode += "continue;\n";
                }
                if (langToConvertTo == "java") {
                    htCode += "continue;\n";
                }
                if (langToConvertTo == "kt") {
                    htCode += "continue\n";
                }
                if (langToConvertTo == "rb") {
                    htCode += "next\n";
                }
                if (langToConvertTo == "nim") {
                    htCode += "continue\n";
                }
                if (langToConvertTo == "ahk") {
                    htCode += "continue\n";
                }
                if (langToConvertTo == "swift") {
                    htCode += "continue\n";
                }
                if (langToConvertTo == "dart") {
                    htCode += "continue;\n";
                }
                if (langToConvertTo == "ts") {
                    htCode += "continue;\n";
                }
                if (langToConvertTo == "groovy") {
                    htCode += "continue;\n";
                }
            }
            else if (StrLower(A_LoopField94) == "::" + keyWordContinue + "::") {
                if (langToConvertTo == langFileExtension_2) {
                    htCode += "::" + keyWordContinue_2 + "::\n";
                }
                if (langToConvertTo == "lua") {
                    htCode += "::continue::\n";
                }
            }
            else if (StrLower(A_LoopField94) == StrLower(keyWordLoopInfinite) || StrLower(A_LoopField94) == StrLower(keyWordLoopInfinite + ":")) {
                // infinity loops
                haveWeEverUsedAloop = 1;
                lineDone = 1;
                if (langToConvertTo == "py") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " , value in enumerate(iter(int, 1), start=" + AHKlikeLoopsIndexedAt + "):";
                }
                if (langToConvertTo == "js") {
                    var1 = "for (let " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; ; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "cpp") {
                    var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; ; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "go") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " := " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < someLimit; " + keyWordAIndex + "" + STR(AindexcharLength) + "++";
                }
                if (langToConvertTo == "lua") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + ", someLimit do";
                }
                if (langToConvertTo == "cs") {
                    var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < someLimit; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "java") {
                    var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < someLimit; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "kt") {
                    var1 = "for (" + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + "..someLimit)";
                }
                if (langToConvertTo == "rb") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + "..someLimit do";
                }
                if (langToConvertTo == "nim") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + "..someLimit:";
                }
                if (langToConvertTo == "ahk") {
                    var1 = "Loop";
                }
                if (langToConvertTo == "swift") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + " ..< someLimit";
                }
                if (langToConvertTo == "dart") {
                    var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < someLimit; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "ts") {
                    var1 = "for (let " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < someLimit; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "groovy") {
                    var1 = "for (" + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + "..someLimit)";
                }
                if (langToConvertTo == langFileExtension_2) {
                    if (usePythonicColonSyntax_2 == "on") {
                        var1 = keyWordLoopInfinite_2 + ":";
                    } else {
                        var1 = keyWordLoopInfinite_2;
                    }
                }
                nothing = "";
                AindexcharLengthStr = nothing + STR(AindexcharLength) + nothing;
                htCodeAcurlyBraceAddSomeVrasFixNL = 1;
                lineDone = 1;
                if (langToConvertTo != "ahk" && langToConvertTo != langFileExtension_2) {
                    htCodeLoopfixa += "nl|itsaersdtgtgfergsdgfsegdfsedAA|" + STR(AindexcharLength) + "\n";
                    htCodeLoopfixa1 = "nl|itsaersdtgtgfergsdgfsegdfsedAA|" + STR(AindexcharLength);
                }
                AindexcharLength++;
                htCode += htCodeLoopfixa1 + "\n" + var1 + "\n";
            }
            else if (SubStr(Trim(StrLower(A_LoopField94)), 1, StrLen(StrLower(keyWordLoop))) == StrLower(keyWordLoop) && SubStr(Trim(StrLower(A_LoopField94)), 1, StrLen(StrLower(keyWordLoop)) + 2) != StrLower(keyWordLoop) + "% " && SubStr(Trim(StrLower(A_LoopField94)), 1, StrLen(StrLower(keyWordLoopParse))) != StrLower(keyWordLoopParse)) {
                out2 = StringTrimLeft(A_LoopField94, StrLen(keyWordLoop));
                out2 = StrReplace(out2, ":", "");
                //MsgBox % out2
                //MsgBox, % out2
                out2 = Trim(out2);
                myVar = out2;
                lineYGI = expressionParserTranspiler(myVar);
                line = lineYGI;
                haveWeEverUsedAloop = 1;
                //MsgBox, % line
                if (langToConvertTo == "py") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in range(" + AHKlikeLoopsIndexedAt + ", " + line + " + " + AHKlikeLoopsIndexedAt + "):";
                }
                if (langToConvertTo == "js") {
                    var1 = "for (let " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "cpp") {
                    var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "go") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " := " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++";
                }
                if (langToConvertTo == "lua") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + ", " + line + " + " + AHKlikeLoopsIndexedAt + " do";
                }
                if (langToConvertTo == "cs") {
                    var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "java") {
                    var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "kt") {
                    var1 = "for (" + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + ".." + line + " + " + AHKlikeLoopsIndexedAt + ")";
                }
                if (langToConvertTo == "rb") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + ".." + line + " + " + AHKlikeLoopsIndexedAt + " do";
                }
                if (langToConvertTo == "nim") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + ".." + line + " + " + AHKlikeLoopsIndexedAt + ":";
                }
                if (langToConvertTo == "ahk") {
                    var1 = "Loop, " + line;
                }
                if (langToConvertTo == "swift") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + " ..< " + line + " + " + AHKlikeLoopsIndexedAt;
                }
                if (langToConvertTo == "dart") {
                    var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "ts") {
                    var1 = "for (let " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "groovy") {
                    var1 = "for (" + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + ".." + line + " + " + AHKlikeLoopsIndexedAt + ")";
                }
                if (langToConvertTo == langFileExtension_2) {
                    if (usePythonicColonSyntax_2 == "on") {
                        var1 = Trim(keyWordLoop_2) + " " + line + ":";
                    } else {
                        var1 = Trim(keyWordLoop_2) + " " + line;
                    }
                }
                nothing = "";
                AindexcharLengthStr = nothing + STR(AindexcharLength) + nothing;
                htCodeAcurlyBraceAddSomeVrasFixNL = 1;
                if (langToConvertTo != "ahk" && langToConvertTo != langFileExtension_2) {
                    htCodeLoopfixa += "nl|itsaersdtgtgfergsdgfsegdfsedAA|" + STR(AindexcharLength) + "\n";
                    htCodeLoopfixa1 = "nl|itsaersdtgtgfergsdgfsegdfsedAA|" + STR(AindexcharLength);
                }
                AindexcharLength++;
                lineDone = 1;
                htCode += htCodeLoopfixa1 + "\n" + var1 + "\n";
            }
            else if (SubStr(Trim(StrLower(A_LoopField94)), 1, StrLen(StrLower(keyWordLoop)) + 2) == StrLower(keyWordLoop) + "% ") {
                out2 = StringTrimLeft(A_LoopField94, StrLen(keyWordLoop) + 2);
                out2 = StrReplace(out2, ":", "");
                //MsgBox % out2
                //MsgBox, % out2
                out2 = Trim(out2);
                myVar = out2;
                lineYGI = expressionParserTranspiler(myVar);
                line = lineYGI;
                haveWeEverUsedAloop = 1;
                //MsgBox, % line
                if (langToConvertTo == "py") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in range(" + AHKlikeLoopsIndexedAt + ", " + line + " + " + AHKlikeLoopsIndexedAt + "):";
                }
                if (langToConvertTo == "js") {
                    var1 = "for (let " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "cpp") {
                    var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "go") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " := " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++";
                }
                if (langToConvertTo == "lua") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + ", " + line + " + " + AHKlikeLoopsIndexedAt + " do";
                }
                if (langToConvertTo == "cs") {
                    var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "java") {
                    var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "kt") {
                    var1 = "for (" + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + ".." + line + " + " + AHKlikeLoopsIndexedAt + ")";
                }
                if (langToConvertTo == "rb") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + ".." + line + " + " + AHKlikeLoopsIndexedAt + " do";
                }
                if (langToConvertTo == "nim") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + ".." + line + " + " + AHKlikeLoopsIndexedAt + ":";
                }
                if (langToConvertTo == "ahk") {
                    var1 = "Loop, % " + line;
                }
                if (langToConvertTo == "swift") {
                    var1 = "for " + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + " ..< " + line + " + " + AHKlikeLoopsIndexedAt;
                }
                if (langToConvertTo == "dart") {
                    var1 = "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "ts") {
                    var1 = "for (let " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < " + line + " + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "groovy") {
                    var1 = "for (" + keyWordAIndex + "" + STR(AindexcharLength) + " in " + AHKlikeLoopsIndexedAt + ".." + line + " + " + AHKlikeLoopsIndexedAt + ")";
                }
                if (langToConvertTo == langFileExtension_2) {
                    if (usePythonicColonSyntax_2 == "on") {
                        var1 = Trim(keyWordLoop_2) + " % " + line + ":";
                    } else {
                        var1 = Trim(keyWordLoop_2) + " % " + line;
                    }
                }
                nothing = "";
                AindexcharLengthStr = nothing + STR(AindexcharLength) + nothing;
                htCodeAcurlyBraceAddSomeVrasFixNL = 1;
                if (langToConvertTo != "ahk" && langToConvertTo != langFileExtension_2) {
                    htCodeLoopfixa += "nl|itsaersdtgtgfergsdgfsegdfsedAA|" + STR(AindexcharLength) + "\n";
                    htCodeLoopfixa1 = "nl|itsaersdtgtgfergsdgfsegdfsedAA|" + STR(AindexcharLength);
                }
                AindexcharLength++;
                lineDone = 1;
                htCode += htCodeLoopfixa1 + "\n" + var1 + "\n";
            }
            else if (SubStr(StrLower(A_LoopField94), 1, StrLen(StrLower(keyWordLoopParse))) == StrLower(keyWordLoopParse)) {
                var1 = StringTrimLeft(A_LoopField94, StrLen(keyWordLoopParse));
                out2 = StrReplace(out2, ":", "");
                lineDone = 1;
                line1 = Trim(StrSplit(var1, ",", 1));
                line1 = expressionParserTranspiler(line1);
                line2 = "";
                line3 = "";
                itemsOut = "";
                line2 = Trim(StrSplit(var1, ",", 2));
                line3 = Trim(StrSplit(var1, ",", 3));
                if (InStr(var1, keyWordEscpaeChar + ",")) {
                    line2 = Chr(34) + "," + Chr(34);
                    if (langToConvertTo == "py") {
                        itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                    }
                    if (langToConvertTo == "js") {
                        itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ");";
                    }
                    if (langToConvertTo == "cpp") {
                        itemsOut = "std::vector<std::string> items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ");";
                    }
                    if (langToConvertTo == "go") {
                        itemsOut = "items" + STR(AindexcharLength) + " := LoopParseFunc(" + line1 + ", " + line2 + ")";
                    }
                    if (langToConvertTo == "lua") {
                        itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                    }
                    if (langToConvertTo == "cs") {
                        itemsOut = "List<string> items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ");";
                    }
                    if (langToConvertTo == "java") {
                        itemsOut = "List<String> items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ");";
                    }
                    if (langToConvertTo == "kt") {
                        itemsOut = "val items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                    }
                    if (langToConvertTo == "rb") {
                        itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                    }
                    if (langToConvertTo == "nim") {
                        itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                    }
                    if (langToConvertTo == "ahk") {
                        itemsOut = "\n";
                    }
                    if (langToConvertTo == "swift") {
                        itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                    }
                    if (langToConvertTo == "dart") {
                        itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                    }
                    if (langToConvertTo == "ts") {
                        itemsOut = "let items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                    }
                    if (langToConvertTo == "groovy") {
                        itemsOut = "def items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                    }
                } else {
                    if (line2 == "" && line3 == "") {
                        // nothing so only each char
                        if (langToConvertTo == "py" || langToConvertTo == "js") {
                            itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ")";
                        }
                        if (langToConvertTo == "cpp") {
                            itemsOut = "std::vector<std::string> items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ");";
                        }
                        if (langToConvertTo == "go") {
                            itemsOut = "items" + STR(AindexcharLength) + " := LoopParseFunc(" + line1 + ")";
                        }
                        if (langToConvertTo == "lua") {
                            itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ")";
                        }
                        if (langToConvertTo == "cs") {
                            itemsOut = "List<string> items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ");";
                        }
                        if (langToConvertTo == "java") {
                            itemsOut = "List<String> items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ");";
                        }
                        if (langToConvertTo == "kt") {
                            itemsOut = "val items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ")";
                        }
                        if (langToConvertTo == "rb") {
                            itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ")";
                        }
                        if (langToConvertTo == "nim") {
                            itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ")";
                        }
                        if (langToConvertTo == "ahk") {
                            itemsOut = "\n";
                        }
                        if (langToConvertTo == "swift") {
                            itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ")";
                        }
                        if (langToConvertTo == "dart") {
                            itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ")";
                        }
                        if (langToConvertTo == "ts") {
                            itemsOut = "let items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ")";
                        }
                        if (langToConvertTo == "groovy") {
                            itemsOut = "def items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ")";
                        }
                    }
                    if (line2 != "" && line3 == "") {
                        if (InStr(line2, keyWordEscpaeChar)) {
                            line2 = Chr(34) + line2 + Chr(34);
                        }
                        if (langToConvertTo == "py" || langToConvertTo == "js") {
                            itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                        }
                        if (langToConvertTo == "cpp") {
                            itemsOut = "std::vector<std::string> items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ");";
                        }
                        if (langToConvertTo == "go") {
                            itemsOut = "items" + STR(AindexcharLength) + " := LoopParseFunc(" + line1 + ", " + line2 + ")";
                        }
                        if (langToConvertTo == "lua") {
                            itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                        }
                        if (langToConvertTo == "cs") {
                            itemsOut = "List<string> items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ");";
                        }
                        if (langToConvertTo == "java") {
                            itemsOut = "List<String> items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ");";
                        }
                        if (langToConvertTo == "kt") {
                            itemsOut = "val items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                        }
                        if (langToConvertTo == "rb") {
                            itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                        }
                        if (langToConvertTo == "nim") {
                            itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                        }
                        if (langToConvertTo == "ahk") {
                            itemsOut = "\n";
                        }
                        if (langToConvertTo == "swift") {
                            itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                        }
                        if (langToConvertTo == "dart") {
                            itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                        }
                        if (langToConvertTo == "ts") {
                            itemsOut = "let items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                        }
                        if (langToConvertTo == "groovy") {
                            itemsOut = "def items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ")";
                        }
                    }
                    if (line2 != "" && line3 != "") {
                        if (InStr(line2, keyWordEscpaeChar)) {
                            line2 = Chr(34) + line2 + Chr(34);
                        }
                        if (InStr(line3, keyWordEscpaeChar)) {
                            line3 = Chr(34) + line3 + Chr(34);
                        }
                        if (langToConvertTo == "py" || langToConvertTo == "js") {
                            itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ")";
                        }
                        if (langToConvertTo == "cpp") {
                            itemsOut = "std::vector<std::string> items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ");";
                        }
                        if (langToConvertTo == "go") {
                            itemsOut = "items" + STR(AindexcharLength) + " := LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ")";
                        }
                        if (langToConvertTo == "lua") {
                            itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ")";
                        }
                        if (langToConvertTo == "cs") {
                            itemsOut = "List<string> items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ");";
                        }
                        if (langToConvertTo == "java") {
                            itemsOut = "List<String> items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ");";
                        }
                        if (langToConvertTo == "kt") {
                            itemsOut = "val items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ")";
                        }
                        if (langToConvertTo == "rb") {
                            itemsOut = "items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ")";
                        }
                        if (langToConvertTo == "nim") {
                            itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ")";
                        }
                        if (langToConvertTo == "ahk") {
                            itemsOut = "\n";
                        }
                        if (langToConvertTo == "swift") {
                            itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ")";
                        }
                        if (langToConvertTo == "dart") {
                            itemsOut = "var items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ")";
                        }
                        if (langToConvertTo == "ts") {
                            itemsOut = "let items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ")";
                        }
                        if (langToConvertTo == "groovy") {
                            itemsOut = "def items" + STR(AindexcharLength) + " = LoopParseFunc(" + line1 + ", " + line2 + ", " + line3 + ")";
                        }
                    }
                    itemsOut = StrReplace(itemsOut, keyWordEscpaeChar, Chr(92));
                }
                if (langToConvertTo == "py") {
                    var1out = itemsOut + "\n" + "for " + keyWordAIndex + "" + STR(AindexcharLength) + " , " + keyWordALoopField + "" + STR(AindexcharLength) + " in enumerate(items" + STR(AindexcharLength) + ", start=" + AHKlikeLoopsIndexedAt + "):";
                }
                if (langToConvertTo == "js") {
                    var1out = itemsOut + "\n" + "for (let " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < items" + STR(AindexcharLength) + ".length + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "cpp") {
                    var1out = itemsOut + "\n" + "for (size_t " + keyWordAIndex + "" + STR(AindexcharLength) + " = " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + " < items" + STR(AindexcharLength) + ".size() + " + AHKlikeLoopsIndexedAt + "; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "go") {
                    var1out = itemsOut + "\n" + "for " + keyWordAIndex + "" + STR(AindexcharLength) + " , " + keyWordALoopField + "" + STR(AindexcharLength) + " := range(items" + STR(AindexcharLength) + ")";
                }
                if (langToConvertTo == "lua") {
                    var1out = itemsOut + "\n" + "for " + keyWordAIndex + "" + STR(AindexcharLength) + " , " + keyWordALoopField + "" + STR(AindexcharLength) + " in ipairs(items" + STR(AindexcharLength) + ") do";
                }
                if (langToConvertTo == "cs") {
                    var1out = itemsOut + "\n" + "foreach (var " + keyWordALoopField + "" + STR(AindexcharLength) + " in items" + STR(AindexcharLength) + ")";
                }
                if (langToConvertTo == "java") {
                    var1out = itemsOut + "\n" + "for (" + keyWordALoopField + "" + STR(AindexcharLength) + " : items" + STR(AindexcharLength) + ")";
                }
                if (langToConvertTo == "kt") {
                    var1out = itemsOut + "\n" + "for (" + keyWordAIndex + "" + STR(AindexcharLength) + " , " + keyWordALoopField + "" + STR(AindexcharLength) + " in items" + STR(AindexcharLength) + ".withIndex())";
                }
                if (langToConvertTo == "rb") {
                    var1out = itemsOut + "\n" + "items" + STR(AindexcharLength) + ".each_with_index do |" + keyWordALoopField + "" + STR(AindexcharLength) + " , " + keyWordAIndex + "" + STR(AindexcharLength) + "|";
                }
                if (langToConvertTo == "nim") {
                    var1out = itemsOut + "\n" + "for " + keyWordAIndex + "" + STR(AindexcharLength) + " , " + keyWordALoopField + "" + STR(AindexcharLength) + " in items" + STR(AindexcharLength) + " | " + keyWordAIndex + "" + STR(AindexcharLength) + " += 1:";
                }
                if (langToConvertTo == "ahk") {
                    var1out = "Loop, Parse, " + line1 + " " + line2 + " " + line3;
                }
                if (langToConvertTo == "swift") {
                    var1out = itemsOut + "\n" + "for (index, " + keyWordALoopField + "" + STR(AindexcharLength) + ") in items" + STR(AindexcharLength) + ".enumerated()";
                }
                if (langToConvertTo == "dart") {
                    var1out = itemsOut + "\n" + "for (int " + keyWordAIndex + "" + STR(AindexcharLength) + " = 0; " + keyWordAIndex + "" + STR(AindexcharLength) + " < items" + STR(AindexcharLength) + ".length; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "ts") {
                    var1out = itemsOut + "\n" + "for (let " + keyWordAIndex + "" + STR(AindexcharLength) + " = 0; " + keyWordAIndex + "" + STR(AindexcharLength) + " < items" + STR(AindexcharLength) + ".length; " + keyWordAIndex + "" + STR(AindexcharLength) + "++)";
                }
                if (langToConvertTo == "groovy") {
                    var1out = itemsOut + "\n" + "items" + STR(AindexcharLength) + ".eachWithIndex { " + keyWordALoopField + "" + STR(AindexcharLength) + " , " + keyWordAIndex + "" + STR(AindexcharLength) + " ->";
                }
                nothing = "";
                AindexcharLengthStr = nothing + STR(AindexcharLength) + nothing;
                //
                //
                theFixTextLoopLP = "";
                if (langToConvertTo == "cpp") {
                    theFixTextLoopLP = "std::string " + keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "];";
                }
                if (langToConvertTo == "js") {
                    theFixTextLoopLP = "const " + keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "];";
                }
                if (langToConvertTo == "go") {
                    theFixTextLoopLP = keyWordALoopField + "" + AindexcharLengthStr + " := items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "]";
                }
                if (langToConvertTo == "lua") {
                    theFixTextLoopLP = keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "]";
                }
                if (langToConvertTo == "cs") {
                    theFixTextLoopLP = keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "]";
                }
                if (langToConvertTo == "java") {
                    theFixTextLoopLP = keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "]";
                }
                if (langToConvertTo == "kt") {
                    theFixTextLoopLP = keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "]";
                }
                if (langToConvertTo == "rb") {
                    theFixTextLoopLP = keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "]";
                }
                if (langToConvertTo == "nim") {
                    theFixTextLoopLP = keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "]";
                }
                if (langToConvertTo == "ahk") {
                    theFixTextLoopLP = "\n";
                }
                if (langToConvertTo == "swift") {
                    theFixTextLoopLP = keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "]";
                }
                if (langToConvertTo == "dart") {
                    theFixTextLoopLP = keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "]";
                }
                if (langToConvertTo == "ts") {
                    theFixTextLoopLP = keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "]";
                }
                if (langToConvertTo == "groovy") {
                    theFixTextLoopLP = keyWordALoopField + "" + AindexcharLengthStr + " = items" + AindexcharLengthStr + "[" + keyWordAIndex + "" + AindexcharLengthStr + " - " + AHKlikeLoopsIndexedAt + "]";
                }
                htCodeAcurlyBraceAddSomeVrasFixLP = 1;
                haveWeEverUsedAloop = 1;
                if (langToConvertTo != "ahk" && langToConvertTo != langFileExtension_2) {
                    htCodeLoopfixa += "lp|itsaersdtgtgfergsdgfsegdfsedAA|" + STR(AindexcharLength) + "\n";
                    htCodeLoopfixa1 = "lp|itsaersdtgtgfergsdgfsegdfsedAA|" + STR(AindexcharLength);
                }
                AindexcharLength++;
                if (langToConvertTo == langFileExtension_2) {
                    if (usePythonicColonSyntax_2 == "on") {
                        htCode += Trim(keyWordLoopParse_2) + " " + var1 + ":\n";
                    } else {
                        htCode += Trim(keyWordLoopParse_2) + " " + var1 + Chr(10);
                    }
                } else {
                    htCode += htCodeLoopfixa1 + Chr(10) + var1out + Chr(10);
                }
            }
            else if (SubStrLastChars(Trim(A_LoopField94), StrLen(keyWordInc)) == keyWordInc || SubStrLastChars(Trim(A_LoopField94), StrLen(keyWordInc + ";")) == keyWordInc + ";" && lineDone == 0) {
                if (useSemicolon == "on") {
                    str1 = Trim(StringTrimRight(Trim(A_LoopField94), StrLen(keyWordInc + ";")));
                } else {
                    str1 = Trim(StringTrimRight(Trim(A_LoopField94), StrLen(keyWordInc)));
                }
                if (langToConvertTo == langFileExtension_2) {
                    if (useSemicolon_2 == "on") {
                        htCode += str1 + keyWordInc_2 + ";" + Chr(10);
                    } else {
                        htCode += str1 + keyWordInc_2 + Chr(10);
                    }
                }
                if (langToConvertTo == "cpp") {
                    htCode += str1 + "++;" + Chr(10);
                }
                if (langToConvertTo == "py") {
                    htCode += str1 + " += 1" + Chr(10);
                }
                if (langToConvertTo == "js") {
                    htCode += str1 + "++;" + Chr(10);
                }
                if (langToConvertTo == "go") {
                    htCode += str1 + "++;" + Chr(10);
                }
                if (langToConvertTo == "lua") {
                    htCode += str1 + " = " + str1 + " + 1" + Chr(10);
                }
                if (langToConvertTo == "cs") {
                    htCode += str1 + "++;" + Chr(10);
                }
                if (langToConvertTo == "java") {
                    htCode += str1 + "++;" + Chr(10);
                }
                if (langToConvertTo == "kt") {
                    htCode += str1 + "++;" + Chr(10);
                }
                if (langToConvertTo == "rb") {
                    htCode += str1 + " += 1" + Chr(10);
                }
                if (langToConvertTo == "nim") {
                    htCode += str1 + " += 1" + Chr(10);
                }
                if (langToConvertTo == "ahk") {
                    htCode += str1 + "++" + Chr(10);
                }
                if (langToConvertTo == "swift") {
                    htCode += str1 + " += 1" + Chr(10);
                }
                if (langToConvertTo == "dart") {
                    htCode += str1 + "++;" + Chr(10);
                }
                if (langToConvertTo == "ts") {
                    htCode += str1 + "++;" + Chr(10);
                }
                if (langToConvertTo == "groovy") {
                    htCode += str1 + "++;" + Chr(10);
                }
            }
            else if (SubStrLastChars(Trim(A_LoopField94), StrLen(keyWordDec)) == keyWordDec || SubStrLastChars(Trim(A_LoopField94), StrLen(keyWordDec + ";")) == keyWordDec + ";" && lineDone == 0) {
                if (useSemicolon == "on") {
                    str1 = Trim(StringTrimRight(Trim(A_LoopField94), StrLen(keyWordDec + ";")));
                } else {
                    str1 = Trim(StringTrimRight(Trim(A_LoopField94), StrLen(keyWordDec)));
                }
                if (langToConvertTo == langFileExtension_2) {
                    if (useSemicolon_2 == "on") {
                        htCode += str1 + keyWordDec_2 + ";" + Chr(10);
                    } else {
                        htCode += str1 + keyWordDec_2 + Chr(10);
                    }
                }
                if (langToConvertTo == "cpp") {
                    htCode += str1 + "--;" + Chr(10);
                }
                if (langToConvertTo == "py") {
                    htCode += str1 + " -= 1" + Chr(10);
                }
                if (langToConvertTo == "js") {
                    htCode += str1 + "--;" + Chr(10);
                }
                if (langToConvertTo == "go") {
                    htCode += str1 + "--;" + Chr(10);
                }
                if (langToConvertTo == "lua") {
                    htCode += str1 + " = " + str1 + " - 1\n";
                }
                if (langToConvertTo == "cs") {
                    htCode += str1 + "--;" + Chr(10);
                }
                if (langToConvertTo == "java") {
                    htCode += str1 + "--;" + Chr(10);
                }
                if (langToConvertTo == "kt") {
                    htCode += str1 + "--;" + Chr(10);
                }
                if (langToConvertTo == "rb") {
                    htCode += str1 + " -= 1" + Chr(10);
                }
                if (langToConvertTo == "nim") {
                    htCode += str1 + " -= 1" + Chr(10);
                }
                if (langToConvertTo == "ahk") {
                    htCode += str1 + "--" + Chr(10);
                }
                if (langToConvertTo == "swift") {
                    htCode += str1 + " -= 1" + Chr(10);
                }
                if (langToConvertTo == "dart") {
                    htCode += str1 + "--;" + Chr(10);
                }
                if (langToConvertTo == "ts") {
                    htCode += str1 + "--;" + Chr(10);
                }
                if (langToConvertTo == "groovy") {
                    htCode += str1 + "--;" + Chr(10);
                }
            }
            else if (SubStr(StrLower(Trim(A_LoopField94)), 1, StrLen(StrLower(keyWordInclude + " "))) == StrLower(keyWordInclude + " ") && langToConvertTo == langFileExtension_2) {
                htCode += keyWordInclude_2 + " " + Trim(StringTrimLeft(Trim(A_LoopField94), StrLen(StrLower(keyWordInclude) + " "))) + "\n";
            }
            else if (StrLower(A_LoopField94) == StrLower(keyWordGlobal) || StrLower(A_LoopField94) == StrLower(keyWordGlobal + ";")) {
                if (langToConvertTo == "ahk") {
                    htCode += "global\n";
                }
            }
            else if (SubStr(StrLower(A_LoopField94), 1, StrLen(StrLower(keyWordAwait))) == StrLower(keyWordAwait)) {
                str1 = StringTrimLeft(A_LoopField94, StrLen(keyWordAwait));
                //MsgBox, % A_LoopField94
                lineDone = 1;
                fixExpertionLineFuncOnly = 1;
                if (langToConvertTo == langFileExtension_2) {
                    if (useSemicolon_2 == "on") {
                        str2 = expressionParserTranspiler(Trim(str1)) + ";";
                    } else {
                        str2 = expressionParserTranspiler(Trim(str1));
                    }
                } else {
                    if (langToConvertTo == "py" || langToConvertTo == "nim" || langToConvertTo == "ahk" || langToConvertTo == "go" || langToConvertTo == "lua" || langToConvertTo == "kt" || langToConvertTo == "rb" || langToConvertTo == "swift" || langToConvertTo == "groovy") {
                        if (SubStrLastChars(str1, 1) == ";") {
                            str1 = StringTrimRight(str1, 1);
                        }
                    }
                    str2 = expressionParserTranspiler(Trim(str1)) + ";";
                    if (langToConvertTo == "py" || langToConvertTo == "nim" || langToConvertTo == "ahk" || langToConvertTo == "go" || langToConvertTo == "lua" || langToConvertTo == "kt" || langToConvertTo == "rb" || langToConvertTo == "swift" || langToConvertTo == "groovy") {
                        if (SubStrLastChars(str2, 1) == ";") {
                            str2 = StringTrimRight(str2, 1);
                        }
                    }
                }
                fixExpertionLineFuncOnly = 0;
                if (langToConvertTo == "js" || langToConvertTo == "ts" || langToConvertTo == langFileExtension_2) {
                    htCode += "await " + str2 + "\n";
                } else {
                    htCode += str2 + "\n";
                }
            }
            else if (SubStr(StrLower(A_LoopField94), 1, StrLen(StrLower(keyWordGlobal))) == StrLower(keyWordGlobal)) {
                str1 = StringTrimLeft(A_LoopField94, StrLen(keyWordGlobal));
                //MsgBox, % A_LoopField94
                str1 = StrReplace(str1, ";", "");
                lineDone = 1;
                if (langToConvertTo == "py" || langToConvertTo == "ahk") {
                    str2 = "global " + str1;
                } else {
                    str2 = "";
                }
                htCode += str2 + "\n";
            }
            else if (A_LoopField94 == "sdghbuheaq8ehgfuowhPSAVBYOFXDSAWHPDIVHXDBOAUHIPXVBOAUHFXDPVOYaushdpzuoyvsdhpxuoazdsfpc") {
                lineDone = 1;
                htCode += A_LoopField94 + Chr(10);
            }
            else if (A_LoopField94 == "sdghbuheaq8ehgfuowhPSAVBYOFXDSAWHPDIVHXDBOAUHIPXVBOAUHFXDPVOYaushdpzuoyvsdhpxuoazdsfpc") {
                lineDone = 1;
                htCode += A_LoopField94 + Chr(10);
            }
            else if (A_LoopField94 == "sdghbuheaq8ehgfuowhPSAVBYOFXDSAWHPDIVHXDBOAUHIPXVBOAUHFXDPVOYaushdpzuoyvsdhpxuoazdsfpc") {
                lineDone = 1;
                htCode += A_LoopField94 + Chr(10);
            }
            else if (SubStr(StrLower(A_LoopField94), 1, StrLen(keyWordFunc)) == keyWordFunc || SubStr(StrLower(A_LoopField94), 1, StrLen(keyWordAsync + keyWordFunc)) == keyWordAsync + keyWordFunc && InStr(A_LoopField94, " main(") == false && lineDone == 0) {
                lineDone = 1;
                if (SubStr(StrLower(A_LoopField94), 1, StrLen(keyWordAsync + keyWordFunc)) == keyWordAsync + keyWordFunc) {
                    // is async
                    int1 = 1;
                    str1 = Trim(StringTrimLeft(A_LoopField94, StrLen(keyWordAsync + keyWordFunc)));
                } else {
                    // is async
                    int1 = 0;
                    str1 = Trim(StringTrimLeft(A_LoopField94, StrLen(keyWordFunc)));
                }
                if (usePrefixTypeForTypeDefinition == "on") {
                    str2 = Trim(StrSplit(str1, "(", 1));
                    // func body
                    str1 = Trim(StringTrimLeft(str1, StrLen(str2)));
                    str1 = StringTrimRight(str1, 1);
                    // type of the func
                    str3 = Trim(StringTrimRight(str2, StrLen(StrSplit(str2, " ", countChars(str2, " ") + 1))));
                    // name of func
                    str2 = Trim(StrSplit(str2, " ", countChars(str2, " ") + 1));
                }
                if (usePostfixTypeForTypeDefinition == "on") {
                    // name of func
                    str2 = Trim(StrSplit(str1, "(", 1));
                    // func body
                    str1 = Trim(StringTrimLeft(str1, StrLen(str2)));
                    // type of the func
                    str3 = Trim(StrSplit(str1, ")", countChars(str1, ")") + 1));
                    str3 = StringTrimLeft(str3, 1);
                    str1 = Trim(StringTrimRight(str1, StrLen(str3) + 2));
                }
                str1 = StringTrimLeft(str1, 1);
                str3 = Trim(str3);
                if (Trim(str1) == "") {
                    if (langToConvertTo == langFileExtension_2) {
                        if (int1 == 1) {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                htCode += keyWordAsync + keyWordFunc + getFuncTypeConvert(str3) + " " + str2 + "()" + Chr(10);
                            } else {
                                htCode += keyWordAsync + keyWordFunc + str2 + "(): " + getFuncTypeConvert(str3) + Chr(10);
                            }
                        } else {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                htCode += keyWordFunc + getFuncTypeConvert(str3) + " " + str2 + "()" + Chr(10);
                            } else {
                                htCode += keyWordFunc + str2 + "(): " + getFuncTypeConvert(str3) + Chr(10);
                            }
                        }
                    }
                    if (langToConvertTo == "cpp") {
                        htCode += getFuncTypeConvert(str3) + " " + str2 + "()" + Chr(10);
                    }
                    if (langToConvertTo == "py") {
                        htCode += "def " + str2 + "():" + Chr(10);
                    }
                    if (langToConvertTo == "js") {
                        if (int1 == 1) {
                            htCode += "async function " + str2 + "()" + Chr(10);
                        } else {
                            htCode += "function " + str2 + "()" + Chr(10);
                        }
                    }
                    // Go
                    if (langToConvertTo == "go") {
                        if (str3 == keyWordVoid) {
                            htCode += "func " + str2 + "()" + Chr(10);
                        } else {
                            htCode += "func " + str2 + "() " + getFuncTypeConvert(str3) + Chr(10);
                        }
                    }
                    if (langToConvertTo == "lua") {
                        htCode += "function " + str2 + "()" + Chr(10);
                    }
                    if (langToConvertTo == "cs") {
                        htCode += "static " + getFuncTypeConvert(str3) + " " + str2 + "()" + Chr(10);
                    }
                    if (langToConvertTo == "java") {
                        htCode += "public static " + getFuncTypeConvert(str3) + " " + str2 + "()" + Chr(10);
                    }
                    if (langToConvertTo == "kt") {
                        if (str3 == keyWordVoid) {
                            htCode += "fun " + str2 + "()" + Chr(10);
                        } else {
                            htCode += "fun " + str2 + "(): " + getFuncTypeConvert(str3) + Chr(10);
                        }
                    }
                    if (langToConvertTo == "rb") {
                        htCode += "def " + str2 + "()" + Chr(10);
                    }
                    if (langToConvertTo == "nim") {
                        if (str3 == keyWordVoid) {
                            htCode += "proc " + str2 + "() =" + Chr(10);
                        } else {
                            htCode += "proc " + str2 + "(): " + getFuncTypeConvert(str3) + " =" + Chr(10);
                        }
                    }
                    if (langToConvertTo == "ahk") {
                        htCode += str2 + "()" + Chr(10);
                    }
                    if (langToConvertTo == "swift") {
                        if (str3 == keyWordVoid) {
                            htCode += "func " + str2 + "()" + Chr(10);
                        } else {
                            htCode += "func " + str2 + "() -> " + getFuncTypeConvert(str3) + Chr(10);
                        }
                    }
                    if (langToConvertTo == "dart") {
                        htCode += getFuncTypeConvert(str3) + " " + str2 + "()" + Chr(10);
                    }
                    if (langToConvertTo == "ts") {
                        htCode += "function " + str2 + "(): " + getFuncTypeConvert(str3) + Chr(10);
                    }
                    if (langToConvertTo == "groovy") {
                        htCode += "def " + str2 + "()" + Chr(10);
                    }
                } else {
                    str5 = "";
                    str6 = "";
                    str7 = "";
                    str8 = "";
                    str9 = "";
                    str10 = "";
                    str11 = "";
                    str12 = "";
                    str13 = "";
                    str14 = "";
                    str15 = "";
                    str16 = "";
                    str17 = "";
                    str18 = "";
                    str19 = "";
                    str20 = "";
                    std::vector<std::string> items95 = LoopParseFunc(str1, ",");
                    for (size_t A_Index95 = 0; A_Index95 < items95.size() + 0; A_Index95++) {
                        std::string A_LoopField95 = items95[A_Index95 - 0];
                        print("|" + Trim(A_LoopField95) + "|");
                        if (InStr(Trim(A_LoopField95), " ")) {
                            // there is space aka there is a type
                            if (InStr(A_LoopField95, " " + Trim(keyWordAssign) + " ") == false) {
                                if (usePrefixTypeForTypeDefinition == "on") {
                                    // normal
                                    str6 = Trim(A_LoopField95);
                                    str7 = getTheLastWord(str6);
                                    str8 = getFuncTypeConvert(Trim(StringTrimRight(str6, StrLen(Trim(str7)) + 1)));
                                    // str5 .= str8 . " " . str7 . Chr(10)
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    // save to str5
                                    // str8 = the type
                                    // str7 = variable name
                                    if (langToConvertTo == langFileExtension_2) {
                                        if (usePrefixTypeForTypeDefinition_2 == "on") {
                                            str5 += str8 + " " + str7 + Chr(10);
                                        } else {
                                            str5 += str7 + ": " + str8 + Chr(10);
                                        }
                                    }
                                    if (langToConvertTo == "cpp") {
                                        str5 += str8 + " " + str7 + Chr(10);
                                    }
                                    if (langToConvertTo == "py") {
                                        str5 += str7 + Chr(10);
                                    }
                                    if (langToConvertTo == "js") {
                                        str5 += str7 + Chr(10);
                                    }
                                    if (langToConvertTo == "go") {
                                        str5 += str7 + " " + str8 + Chr(10);
                                    }
                                    if (langToConvertTo == "lua") {
                                        str5 += str7 + Chr(10);
                                    }
                                    if (langToConvertTo == "cs") {
                                        str5 += str8 + " " + str7 + Chr(10);
                                    }
                                    if (langToConvertTo == "java") {
                                        str5 += str8 + " " + str7 + Chr(10);
                                    }
                                    if (langToConvertTo == "kt") {
                                        str5 += str7 + ": " + str8 + Chr(10);
                                    }
                                    if (langToConvertTo == "rb") {
                                        str5 += str7 + Chr(10);
                                    }
                                    if (langToConvertTo == "nim") {
                                        str5 += str7 + ": " + str8 + Chr(10);
                                    }
                                    if (langToConvertTo == "ahk") {
                                        str5 += str7 + Chr(10);
                                    }
                                    if (langToConvertTo == "swift") {
                                        str5 += "_ " + str7 + ": " + str8 + Chr(10);
                                    }
                                    if (langToConvertTo == "dart") {
                                        str5 += str8 + " " + str7 + Chr(10);
                                    }
                                    if (langToConvertTo == "ts") {
                                        str5 += str7 + ": " + str8 + Chr(10);
                                    }
                                    if (langToConvertTo == "groovy") {
                                        str5 += str7 + Chr(10);
                                    }
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                } else {
                                    // not normal
                                    str6 = Trim(A_LoopField95);
                                    str7 = Trim(StrSplit(str6, ":", 1));
                                    str8 = getFuncTypeConvert(Trim(StrSplit(str6, ":", 2)));
                                    // str5 .= str7 . " :" . str8 . Chr(10)
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    // save to str5
                                    // str8 = the type
                                    // str7 = variable name
                                    if (langToConvertTo == langFileExtension_2) {
                                        if (usePrefixTypeForTypeDefinition_2 == "on") {
                                            str5 += str8 + " " + str7 + Chr(10);
                                        } else {
                                            str5 += str7 + ": " + str8 + Chr(10);
                                        }
                                    }
                                    if (langToConvertTo == "cpp") {
                                        str5 += str8 + " " + str7 + Chr(10);
                                    }
                                    if (langToConvertTo == "py") {
                                        str5 += str7 + Chr(10);
                                    }
                                    if (langToConvertTo == "js") {
                                        str5 += str7 + Chr(10);
                                    }
                                    if (langToConvertTo == "go") {
                                        str5 += str7 + " " + str8 + Chr(10);
                                    }
                                    if (langToConvertTo == "lua") {
                                        str5 += str7 + Chr(10);
                                    }
                                    if (langToConvertTo == "cs") {
                                        str5 += str8 + " " + str7 + Chr(10);
                                    }
                                    if (langToConvertTo == "java") {
                                        str5 += str8 + " " + str7 + Chr(10);
                                    }
                                    if (langToConvertTo == "kt") {
                                        str5 += str7 + ": " + str8 + Chr(10);
                                    }
                                    if (langToConvertTo == "rb") {
                                        str5 += str7 + Chr(10);
                                    }
                                    if (langToConvertTo == "nim") {
                                        str5 += str7 + ": " + str8 + Chr(10);
                                    }
                                    if (langToConvertTo == "ahk") {
                                        str5 += str7 + Chr(10);
                                    }
                                    if (langToConvertTo == "swift") {
                                        str5 += "_ " + str7 + ": " + str8 + Chr(10);
                                    }
                                    if (langToConvertTo == "dart") {
                                        str5 += str8 + " " + str7 + Chr(10);
                                    }
                                    if (langToConvertTo == "ts") {
                                        str5 += str7 + ": " + str8 + Chr(10);
                                    }
                                    if (langToConvertTo == "groovy") {
                                        str5 += str7 + Chr(10);
                                    }
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                }
                            } else {
                                // optanal param
                                if (InStr(Trim(StrSplit(Trim(A_LoopField95), " " + Trim(keyWordAssign) + " ", 1)), " ")) {
                                    // there is a type
                                    if (usePrefixTypeForTypeDefinition == "on") {
                                        // normal
                                        str6 = Trim(StrSplit(Trim(A_LoopField95), " " + Trim(keyWordAssign) + " ", 1));
                                        str9 = Trim(expressionParserTranspiler(Trim(StrSplit(Trim(A_LoopField95), " " + Trim(keyWordAssign) + " ", 2))));
                                        str7 = getTheLastWord(str6);
                                        str8 = getFuncTypeConvert(Trim(StringTrimRight(str6, StrLen(Trim(str7)) + 1)));
                                        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        //;;;;;;;;;;;;;;;; optanal param ;;;;;;;;;;;;;;;;;
                                        // save to str10
                                        // str8 = the type
                                        // str7 = variable name
                                        // str9 = after the keyWordAssign
                                        if (langToConvertTo == langFileExtension_2) {
                                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                                str10 += str8 + " " + str7 + " " + Trim(keyWordAssign_2) + " " + str9 + Chr(10);
                                            } else {
                                                str10 += str7 + ": " + str8 + " " + Trim(keyWordAssign_2) + " " + str9 + Chr(10);
                                            }
                                        }
                                        if (langToConvertTo == "cpp") {
                                            str10 += str8 + " " + str7 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "py") {
                                            str10 += str7 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "js") {
                                            str10 += str7 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "go") {
                                            skipLeftCuleyForFuncPLS = 1;
                                            str10 += str7 + " " + str8 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "lua") {
                                            str10 += str7 + " = " + str9 + Chr(10);
                                            skipLeftCuleyForFuncPLS = 1;
                                        }
                                        if (langToConvertTo == "cs") {
                                            str10 += str8 + " " + str7 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "java") {
                                            str10 += str8 + " " + str7 + " = " + str9 + Chr(10);
                                            skipLeftCuleyForFuncPLS = 1;
                                        }
                                        if (langToConvertTo == "kt") {
                                            str10 += str7 + ": " + str8 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "rb") {
                                            str10 += str7 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "nim") {
                                            str10 += str7 + ": " + str8 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "ahk") {
                                            str10 += str7 + " := " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "swift") {
                                            str10 += "_ " + str7 + ": " + str8 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "dart") {
                                            str10 += str8 + " " + str7 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "ts") {
                                            str10 += str7 + ": " + str8 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "groovy") {
                                            str10 += str7 + " = " + str9 + Chr(10);
                                        }
                                        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        // str10
                                        // skipLeftCuleyForFuncPLS := 1
                                    } else {
                                        // not normal
                                        str6 = Trim(StrSplit(Trim(A_LoopField95), " " + Trim(keyWordAssign) + " ", 1));
                                        str9 = Trim(expressionParserTranspiler(Trim(StrSplit(Trim(A_LoopField95), " " + Trim(keyWordAssign) + " ", 2))));
                                        str7 = Trim(StrSplit(str6, ":", 1));
                                        str8 = getFuncTypeConvert(Trim(StrSplit(str6, ":", 2)));
                                        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        //;;;;;;;;;;;;;;;; optanal param ;;;;;;;;;;;;;;;;;
                                        // save to str10
                                        // str8 = the type
                                        // str7 = variable name
                                        // str9 = after the keyWordAssign
                                        if (langToConvertTo == langFileExtension_2) {
                                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                                str10 += str8 + " " + str7 + " " + Trim(keyWordAssign_2) + " " + str9 + Chr(10);
                                            } else {
                                                str10 += str7 + ": " + str8 + " " + Trim(keyWordAssign_2) + " " + str9 + Chr(10);
                                            }
                                        }
                                        if (langToConvertTo == "cpp") {
                                            str10 += str8 + " " + str7 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "py") {
                                            str10 += str7 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "js") {
                                            str10 += str7 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "go") {
                                            skipLeftCuleyForFuncPLS = 1;
                                            str10 += str7 + " " + str8 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "lua") {
                                            str10 += str7 + " = " + str9 + Chr(10);
                                            skipLeftCuleyForFuncPLS = 1;
                                        }
                                        if (langToConvertTo == "cs") {
                                            str10 += str8 + " " + str7 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "java") {
                                            str10 += str8 + " " + str7 + " = " + str9 + Chr(10);
                                            skipLeftCuleyForFuncPLS = 1;
                                        }
                                        if (langToConvertTo == "kt") {
                                            str10 += str7 + ": " + str8 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "rb") {
                                            str10 += str7 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "nim") {
                                            str10 += str7 + ": " + str8 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "ahk") {
                                            str10 += str7 + " := " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "swift") {
                                            str10 += "_ " + str7 + ": " + str8 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "dart") {
                                            str10 += str8 + " " + str7 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "ts") {
                                            str10 += str7 + ": " + str8 + " = " + str9 + Chr(10);
                                        }
                                        if (langToConvertTo == "groovy") {
                                            str10 += str7 + " = " + str9 + Chr(10);
                                        }
                                        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                        // str10
                                        // skipLeftCuleyForFuncPLS := 1
                                    }
                                } else {
                                    // there is no type
                                    str8 = Trim(StrSplit(Trim(A_LoopField95), " " + Trim(keyWordAssign) + " ", 1));
                                    str9 = Trim(expressionParserTranspiler(Trim(StrSplit(Trim(A_LoopField95), " " + Trim(keyWordAssign) + " ", 2))));
                                    // str10
                                    // skipLeftCuleyForFuncPLS := 1
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    //;;;;;;;;;;;;;;;; optanal param ;;;;;;;;;;;;;;;;;
                                    // save to str10
                                    // str8 = variable name
                                    // str9 = after the keyWordAssign
                                    if (langToConvertTo == langFileExtension_2) {
                                        if (usePrefixTypeForTypeDefinition_2 == "on") {
                                            str10 += str7 + " " + Trim(keyWordAssign_2) + " " + str9 + Chr(10);
                                        } else {
                                            str10 += str7 + " " + Trim(keyWordAssign_2) + " " + str9 + Chr(10);
                                        }
                                    }
                                    if (langToConvertTo == "py") {
                                        str10 += str7 + " = " + str9 + Chr(10);
                                    }
                                    if (langToConvertTo == "js") {
                                        str10 += str7 + " = " + str9 + Chr(10);
                                    }
                                    if (langToConvertTo == "lua") {
                                        str10 += str7 + " = " + str9 + Chr(10);
                                        skipLeftCuleyForFuncPLS = 1;
                                    }
                                    if (langToConvertTo == "rb") {
                                        str10 += str7 + " = " + str9 + Chr(10);
                                    }
                                    if (langToConvertTo == "ahk") {
                                        str10 += str7 + " := " + str9 + Chr(10);
                                    }
                                    if (langToConvertTo == "groovy") {
                                        str10 += str7 + " = " + str9 + Chr(10);
                                    }
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                    //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
                                }
                            }
                        } else {
                            str5 += Trim(A_LoopField95) + Chr(10);
                        }
                    }
                    print(str5);
                    print(str10);
                    if (Trim(str5) != "") {
                        str5 = StringTrimRight(str5, 1);
                    }
                    if (Trim(str10) != "") {
                        str10 = StringTrimRight(str10, 1);
                    }
                    str5 = Trim(str5);
                    str10 = Trim(str10);
                    if (Trim(str5) != "" && Trim(str10) != "") {
                        std::vector<std::string> items96 = LoopParseFunc(str5, "\n", "\r");
                        for (size_t A_Index96 = 0; A_Index96 < items96.size() + 0; A_Index96++) {
                            std::string A_LoopField96 = items96[A_Index96 - 0];
                            str11 += A_LoopField96 + ", ";
                        }
                        std::vector<std::string> items97 = LoopParseFunc(str10, "\n", "\r");
                        for (size_t A_Index97 = 0; A_Index97 < items97.size() + 0; A_Index97++) {
                            std::string A_LoopField97 = items97[A_Index97 - 0];
                            str12 += A_LoopField97 + ", ";
                        }
                        str12 = StringTrimRight(str12, 2);
                        if (langToConvertTo == "dart") {
                            str12 = "[" + str12 + "]";
                        }
                        if (langToConvertTo == "lua") {
                            std::vector<std::string> items98 = LoopParseFunc(str12, ",");
                            for (size_t A_Index98 = 0; A_Index98 < items98.size() + 0; A_Index98++) {
                                std::string A_LoopField98 = items98[A_Index98 - 0];
                                str14 += Trim(StrSplit(Trim(A_LoopField98), " = ", 1)) + ", ";
                            }
                            str14 = StringTrimRight(str14, 2);
                            str13 += "{" + Chr(10);
                            std::vector<std::string> items99 = LoopParseFunc(str12, ",");
                            for (size_t A_Index99 = 0; A_Index99 < items99.size() + 0; A_Index99++) {
                                std::string A_LoopField99 = items99[A_Index99 - 0];
                                str13 += Trim(StrSplit(Trim(A_LoopField99), " = ", 1)) + " = " + Trim(StrSplit(Trim(A_LoopField99), " = ", 1)) + " or " + Trim(StrSplit(Trim(A_LoopField99), " = ", 2)) + Chr(10);
                            }
                            str12 = str14;
                        }
                        if (langToConvertTo == "go") {
                            str14 = "__HTVM_V2_TO_GO_optionalParams__ ...interface{}";
                            str13 += "{" + Chr(10) + "var ";
                            std::vector<std::string> items100 = LoopParseFunc(str12, ",");
                            for (size_t A_Index100 = 0; A_Index100 < items100.size() + 0; A_Index100++) {
                                std::string A_LoopField100 = items100[A_Index100 - 0];
                                str13 += Trim(StrSplit(Trim(StrSplit(Trim(A_LoopField100), " = ", 1)), " ", 1)) + ", ";
                            }
                            str13 = StringTrimRight(str13, 2);
                            str13 += " interface{}" + Chr(10);
                            std::vector<std::string> items101 = LoopParseFunc(str12, ",");
                            for (size_t A_Index101 = 0; A_Index101 < items101.size() + 0; A_Index101++) {
                                std::string A_LoopField101 = items101[A_Index101 - 0];
                                str16 = Trim(StrSplit(Trim(StrSplit(Trim(A_LoopField101), " = ", 1)), " ", 1));
                                str17 = Trim(StrSplit(Trim(A_LoopField101), " = ", 2));
                                str13 += "if len(__HTVM_V2_TO_GO_optionalParams__) " + Chr(62) + " " + STR(A_Index101) + Chr(10) + "{" + Chr(10) + str16 + " = __HTVM_V2_TO_GO_optionalParams__[" + STR(A_Index101) + "]" + Chr(10) + "}" + Chr(10) + "else" + Chr(10) + "{" + Chr(10) + str16 + " = " + str17 + Chr(10) + "}" + Chr(10);
                            }
                            str12 = str14;
                        }
                        if (langToConvertTo == "java") {
                            str14 = "Object... __HTVM_V2_TO_JAVA_optionalParams__";
                            str13 += "{" + Chr(10);
                            std::vector<std::string> items102 = LoopParseFunc(str12, ",");
                            for (size_t A_Index102 = 0; A_Index102 < items102.size() + 0; A_Index102++) {
                                std::string A_LoopField102 = items102[A_Index102 - 0];
                                str13 += Trim(A_LoopField102) + ";" + Chr(10);
                            }
                            std::vector<std::string> items103 = LoopParseFunc(str12, ",");
                            for (size_t A_Index103 = 0; A_Index103 < items103.size() + 0; A_Index103++) {
                                std::string A_LoopField103 = items103[A_Index103 - 0];
                                str16 = Trim(StrSplit(Trim(StrSplit(Trim(A_LoopField103), " = ", 1)), " ", 2));
                                str17 = Trim(StrSplit(Trim(StrSplit(Trim(A_LoopField103), " = ", 1)), " ", 1));
                                // str16 = var name
                                // str17 = type name
                                str13 += "if (__HTVM_V2_TO_JAVA_optionalParams__.length " + Chr(62) + " " + STR(A_Index103) + ") " + str16 + " = (" + str17 + ") __HTVM_V2_TO_JAVA_optionalParams__[" + STR(A_Index103) + "];" + Chr(10);
                            }
                            str12 = str14;
                        }
                        str11 += str12;
                    }
                    if (Trim(str5) != "" && Trim(str10) == "") {
                        std::vector<std::string> items104 = LoopParseFunc(str5, "\n", "\r");
                        for (size_t A_Index104 = 0; A_Index104 < items104.size() + 0; A_Index104++) {
                            std::string A_LoopField104 = items104[A_Index104 - 0];
                            str11 += A_LoopField104 + ", ";
                        }
                        str11 = StringTrimRight(str11, 2);
                    }
                    if (Trim(str5) == "" && Trim(str10) != "") {
                        std::vector<std::string> items105 = LoopParseFunc(str10, "\n", "\r");
                        for (size_t A_Index105 = 0; A_Index105 < items105.size() + 0; A_Index105++) {
                            std::string A_LoopField105 = items105[A_Index105 - 0];
                            str11 += A_LoopField105 + ", ";
                        }
                        str11 = StringTrimRight(str11, 2);
                        if (langToConvertTo == "dart") {
                            str11 = "[" + str11 + "]";
                        }
                        if (langToConvertTo == "lua") {
                            std::vector<std::string> items106 = LoopParseFunc(str11, ",");
                            for (size_t A_Index106 = 0; A_Index106 < items106.size() + 0; A_Index106++) {
                                std::string A_LoopField106 = items106[A_Index106 - 0];
                                str14 += Trim(StrSplit(Trim(A_LoopField106), " = ", 1)) + ", ";
                            }
                            str14 = StringTrimRight(str14, 2);
                            str13 += "{" + Chr(10);
                            std::vector<std::string> items107 = LoopParseFunc(str11, ",");
                            for (size_t A_Index107 = 0; A_Index107 < items107.size() + 0; A_Index107++) {
                                std::string A_LoopField107 = items107[A_Index107 - 0];
                                str13 += Trim(StrSplit(Trim(A_LoopField107), " = ", 1)) + " = " + Trim(StrSplit(Trim(A_LoopField107), " = ", 1)) + " or " + Trim(StrSplit(Trim(A_LoopField107), " = ", 2)) + Chr(10);
                            }
                            str11 = str14;
                        }
                        if (langToConvertTo == "go") {
                            str14 = "__HTVM_V2_TO_GO_optionalParams__ ...interface{}";
                            str13 += "{" + Chr(10) + "var ";
                            std::vector<std::string> items108 = LoopParseFunc(str11, ",");
                            for (size_t A_Index108 = 0; A_Index108 < items108.size() + 0; A_Index108++) {
                                std::string A_LoopField108 = items108[A_Index108 - 0];
                                str13 += Trim(StrSplit(Trim(StrSplit(Trim(A_LoopField108), " = ", 1)), " ", 1)) + ", ";
                            }
                            str13 = StringTrimRight(str13, 2);
                            str13 += " interface{}" + Chr(10);
                            std::vector<std::string> items109 = LoopParseFunc(str11, ",");
                            for (size_t A_Index109 = 0; A_Index109 < items109.size() + 0; A_Index109++) {
                                std::string A_LoopField109 = items109[A_Index109 - 0];
                                str16 = Trim(StrSplit(Trim(StrSplit(Trim(A_LoopField109), " = ", 1)), " ", 1));
                                str17 = Trim(StrSplit(Trim(A_LoopField109), " = ", 2));
                                str13 += "if len(__HTVM_V2_TO_GO_optionalParams__) " + Chr(62) + " " + STR(A_Index109) + Chr(10) + "{" + Chr(10) + str16 + " = __HTVM_V2_TO_GO_optionalParams__[" + STR(A_Index109) + "]" + Chr(10) + "}" + Chr(10) + "else" + Chr(10) + "{" + Chr(10) + str16 + " = " + str17 + Chr(10) + "}" + Chr(10);
                            }
                            str11 = str14;
                        }
                        if (langToConvertTo == "java") {
                            str14 = "Object... __HTVM_V2_TO_JAVA_optionalParams__";
                            str13 += "{" + Chr(10);
                            std::vector<std::string> items110 = LoopParseFunc(str11, ",");
                            for (size_t A_Index110 = 0; A_Index110 < items110.size() + 0; A_Index110++) {
                                std::string A_LoopField110 = items110[A_Index110 - 0];
                                str13 += Trim(A_LoopField110) + ";" + Chr(10);
                            }
                            std::vector<std::string> items111 = LoopParseFunc(str11, ",");
                            for (size_t A_Index111 = 0; A_Index111 < items111.size() + 0; A_Index111++) {
                                std::string A_LoopField111 = items111[A_Index111 - 0];
                                str16 = Trim(StrSplit(Trim(StrSplit(Trim(A_LoopField111), " = ", 1)), " ", 2));
                                str17 = Trim(StrSplit(Trim(StrSplit(Trim(A_LoopField111), " = ", 1)), " ", 1));
                                // str16 = var name
                                // str17 = type name
                                str13 += "if (__HTVM_V2_TO_JAVA_optionalParams__.length " + Chr(62) + " " + STR(A_Index111) + ") " + str16 + " = (" + str17 + ") __HTVM_V2_TO_JAVA_optionalParams__[" + STR(A_Index111) + "];" + Chr(10);
                            }
                            str11 = str14;
                        }
                    }
                    print(str11);
                    //;;;;;;; last put all
                    //;;;;;;; last put all
                    //;;;;;;; last put all
                    if (langToConvertTo == langFileExtension_2) {
                        if (int1 == 1) {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                htCode += keyWordAsync + keyWordFunc + getFuncTypeConvert(str3) + " " + str2 + "(" + str11 + ")" + Chr(10);
                            } else {
                                htCode += keyWordAsync + keyWordFunc + str2 + "(" + str11 + "): " + getFuncTypeConvert(str3) + Chr(10);
                            }
                        } else {
                            if (usePrefixTypeForTypeDefinition_2 == "on") {
                                htCode += keyWordFunc + getFuncTypeConvert(str3) + " " + str2 + "(" + str11 + ")" + Chr(10);
                            } else {
                                htCode += keyWordFunc + str2 + "(" + str11 + "): " + getFuncTypeConvert(str3) + Chr(10);
                            }
                        }
                    }
                    if (langToConvertTo == "cpp") {
                        htCode += getFuncTypeConvert(str3) + " " + str2 + "(" + str11 + ")" + Chr(10);
                    }
                    if (langToConvertTo == "py") {
                        htCode += "def " + str2 + "(" + str11 + "):" + Chr(10);
                    }
                    if (langToConvertTo == "js") {
                        if (int1 == 1) {
                            htCode += "async function " + str2 + "(" + str11 + ")" + Chr(10);
                        } else {
                            htCode += "function " + str2 + "(" + str11 + ")" + Chr(10);
                        }
                    }
                    // Go
                    if (langToConvertTo == "go") {
                        if (str3 == keyWordVoid) {
                            htCode += "func " + str2 + "(" + str11 + ")" + Chr(10) + str13;
                        } else {
                            htCode += "func " + str2 + "(" + str11 + ") " + getFuncTypeConvert(str3) + Chr(10) + str13;
                        }
                    }
                    if (langToConvertTo == "lua") {
                        htCode += "function " + str2 + "(" + str11 + ")" + Chr(10) + str13;
                    }
                    if (langToConvertTo == "cs") {
                        htCode += "static " + getFuncTypeConvert(str3) + " " + str2 + "(" + str11 + ")" + Chr(10);
                    }
                    if (langToConvertTo == "java") {
                        htCode += "public static " + getFuncTypeConvert(str3) + " " + str2 + "(" + str11 + ")" + Chr(10) + str13;
                    }
                    if (langToConvertTo == "kt") {
                        if (str3 == keyWordVoid) {
                            htCode += "fun " + str2 + "(" + str11 + ")" + Chr(10);
                        } else {
                            htCode += "fun " + str2 + "(" + str11 + "): " + getFuncTypeConvert(str3) + Chr(10);
                        }
                    }
                    if (langToConvertTo == "rb") {
                        htCode += "def " + str2 + "(" + str11 + ")" + Chr(10);
                    }
                    if (langToConvertTo == "nim") {
                        if (str3 == keyWordVoid) {
                            htCode += "proc " + str2 + "(" + str11 + ") =" + Chr(10);
                        } else {
                            htCode += "proc " + str2 + "(" + str11 + "): " + getFuncTypeConvert(str3) + " =" + Chr(10);
                        }
                    }
                    if (langToConvertTo == "ahk") {
                        htCode += str2 + "(" + str11 + ")" + Chr(10);
                    }
                    if (langToConvertTo == "swift") {
                        if (str3 == keyWordVoid) {
                            htCode += "func " + str2 + "(" + str11 + ")" + Chr(10);
                        } else {
                            htCode += "func " + str2 + "(" + str11 + ") -> " + getFuncTypeConvert(str3) + Chr(10);
                        }
                    }
                    if (langToConvertTo == "dart") {
                        htCode += getFuncTypeConvert(str3) + " " + str2 + "(" + str11 + ")" + Chr(10);
                    }
                    if (langToConvertTo == "ts") {
                        htCode += "function " + str2 + "(" + str11 + "): " + getFuncTypeConvert(str3) + Chr(10);
                    }
                    if (langToConvertTo == "groovy") {
                        htCode += "def " + str2 + "(" + str11 + ")" + Chr(10);
                    }
                    //;;;;;;; last put all
                    //;;;;;;; last put all
                    //;;;;;;; last put all
                }
            }
            else if (InStr(A_LoopField94, "public static void main(String[] args)") && lineDone == 0) {
                javaMainFuncSeen = 1;
            }
            else if (RegExMatch(Trim(A_LoopField94), "^[a-zA-Z_][a-zA-Z0-9_]*: [^:]*;?$") && usePostfixTypeForTypeDefinition == "on" && lineDone == 0) {
                lineDone = 1;
                //getFuncTypeConvert()
                str1 = Trim(A_LoopField94);
                if (SubStrLastChars(str1, 1) == ";") {
                    str1 = StringTrimRight(str1, 1);
                }
                str2 = Trim(StrSplit(str1, ":", 1));
                str3 = getFuncTypeConvert(Trim(StrSplit(str1, ":", 2)));
                // str2 = var name
                // str3 = type
                if (langToConvertTo == langFileExtension_2) {
                    if (useSemicolon_2 == "on") {
                        if (usePrefixTypeForTypeDefinition_2 == "on") {
                            str4 = str3 + " " + str2 + ";";
                        } else {
                            str4 = str2 + " " + str3 + ";";
                        }
                    } else {
                        if (usePrefixTypeForTypeDefinition_2 == "on") {
                            str4 = str3 + " " + str2;
                        } else {
                            str4 = str2 + " " + str3;
                        }
                    }
                }
                if (langToConvertTo == "cpp") {
                    str4 = str3 + " " + str2 + ";";
                }
                if (langToConvertTo == "py") {
                    str4 = str2 + " = None";
                }
                if (langToConvertTo == "js") {
                    if (useInJavaScriptAlwaysUseVar == "on") {
                        str4 = "var " + str2 + ";";
                    } else {
                        str4 = "let " + str2 + ";";
                    }
                }
                if (langToConvertTo == "go") {
                    str4 = "var " + str2 + " " + str3;
                }
                if (langToConvertTo == "lua") {
                    str4 = str2 + " = nil";
                }
                if (langToConvertTo == "cs") {
                    str4 = str3 + " " + str2 + ";";
                }
                if (langToConvertTo == "java") {
                    if (javaMainFuncSeen == 1) {
                        str4 = str3 + " " + str2 + ";";
                    } else {
                        str4 = "static " + str3 + " " + str2 + ";";
                    }
                }
                if (langToConvertTo == "kt") {
                    str4 = "var " + str2 + ": " + str3 + "? = null";
                }
                if (langToConvertTo == "rb") {
                    str4 = str2 + " = nil";
                }
                if (langToConvertTo == "nim") {
                    str4 = str2 + ": " + str3;
                }
                if (langToConvertTo == "ahk") {
                    str4 = str2 + " := " + Chr(10) + Chr(10);
                }
                if (langToConvertTo == "swift") {
                    str4 = "var " + str2 + ": " + str3;
                }
                if (langToConvertTo == "dart") {
                    str4 = str2 + "? " + str3 + ";";
                }
                if (langToConvertTo == "ts") {
                    if (useInJavaScriptAlwaysUseVar == "on") {
                        str4 = "var " + str2 + ";";
                    } else {
                        str4 = "let " + str2 + ";";
                    }
                }
                if (langToConvertTo == "groovy") {
                    str4 = "def " + str2;
                }
                htCode += str4 + Chr(10);
            }
            else if ((SubStr(Trim(A_LoopField94), -2) == ");" || SubStr(Trim(A_LoopField94), -1) == ")") && !(InStr(A_LoopField94, " main(")) && lineDone == 0) {
                lineDone = 1;
                str1 = Trim(A_LoopField94);
                fixExpertionLineFuncOnly = 1;
                if (langToConvertTo == langFileExtension_2) {
                    if (useSemicolon_2 == "on") {
                        str2 = expressionParserTranspiler(Trim(str1)) + ";";
                    } else {
                        str2 = expressionParserTranspiler(Trim(str1));
                    }
                } else {
                    if (langToConvertTo == "py" || langToConvertTo == "nim" || langToConvertTo == "ahk" || langToConvertTo == "go" || langToConvertTo == "lua" || langToConvertTo == "kt" || langToConvertTo == "rb" || langToConvertTo == "swift" || langToConvertTo == "groovy") {
                        if (SubStrLastChars(str1, 1) == ";") {
                            str1 = StringTrimRight(str1, 1);
                        }
                    }
                    str2 = expressionParserTranspiler(Trim(str1)) + ";";
                    if (langToConvertTo == "py" || langToConvertTo == "nim" || langToConvertTo == "ahk" || langToConvertTo == "go" || langToConvertTo == "lua" || langToConvertTo == "kt" || langToConvertTo == "rb" || langToConvertTo == "swift" || langToConvertTo == "groovy") {
                        if (SubStrLastChars(str2, 1) == ";") {
                            str2 = StringTrimRight(str2, 1);
                        }
                    }
                }
                fixExpertionLineFuncOnly = 0;
                htCode += str2 + "\n";
            }
            else if (KeyWordsCommands(A_LoopField94, "check", commands, langToConvertTo) == "true" && lineDone == 0) {
                lineDone = 1;
                if (langToConvertTo == langFileExtension_2) {
                    htCode += A_LoopField94 + "\n";
                } else {
                    out_KeyWordsCommands = KeyWordsCommands(A_LoopField94, "transpile", commands, langToConvertTo);
                    htCode += out_KeyWordsCommands + "\n";
                }
            } else {
                //print("else else else " . A_LoopField94)
                // this is THE else
                if (lineDone != 1) {
                    if (skipLeftCuleyForFuncPLS != 1) {
                        if (SubStr(Trim(StrLower(A_LoopField94)), 1, 1) == Chr(125)) {
                            htCode += Chr(125) + "\n";
                        } else {
                            if (htCodeAcurlyBraceAddSomeVrasFixLP == 1 && SubStr(Trim(StrLower(A_LoopField94)), 1, 1) == Chr(123)) {
                                htCodeAcurlyBraceAddSomeVrasFixLP = 0;
                                htCode += A_LoopField94 + "\n" + theFixTextLoopLP + "\n";
                            } else {
                                if (htCodeAcurlyBraceAddSomeVrasFixNL == 1 && SubStr(Trim(StrLower(A_LoopField94)), 1, 1) == Chr(123)) {
                                    htCodeAcurlyBraceAddSomeVrasFixNL = 0;
                                    htCode += A_LoopField94 + "\n" + theFixTextLoopNL + "\n";
                                } else {
                                    htCode += A_LoopField94 + "\n";
                                }
                            }
                        }
                    } else {
                        skipLeftCuleyForFuncPLS = 0;
                    }
                }
            }
        }
        htCode = StringTrimRight(htCode, 1);
        //s
        //s
        //s
        if (langToConvertTo != "ahk" && langToConvertTo != langFileExtension_2) {
            //s
            if (haveWeEverUsedAloop == 1) {
                htCodeLoopfixa = StringTrimRight(htCodeLoopfixa, 1);
                //OutputDebug, |%htCodeLoopfixa%|
                AIndexLoopCurlyFix = 1;
                std::vector<std::string> items112 = LoopParseFunc(htCodeLoopfixa, "\n", "\r");
                for (size_t A_Index112 = 0; A_Index112 < items112.size() + 0; A_Index112++) {
                    std::string A_LoopField112 = items112[A_Index112 - 0];
                    sstr123 = A_LoopField112;
                    fixLoopLokingFor = A_LoopField112;
                    fixLoopLokingForfound = 1;
                    out1 = StrSplit(sstr123 ,"|" , 1);
                    out2 = StrSplit(sstr123 ,"|" , 3);
                    //OutputDebug, |%out1%|
                    //OutputDebug, |%out2%|
                    wasAtanyIfsElseAddAIndexLoopCurlyFix = 0;
                    if (out1 == "nl") {
                        inTarget = 0;
                        insideBracket = 0;
                        netsedCurly = 0;
                        eldLoopNestedBADlol = 0;
                        readyToEnd = 0;
                        endBracketDOntPutThere = 0;
                        dontSaveStr = 0;
                        weAreDoneHereCurly = 0;
                        DeleayOneCuzOfLoopParse = 0;
                        fixLoopLokingForNum = 0;
                        insdeAnestedLoopBAD = 0;
                        foundTheTopLoop = 0;
                        out4758686d86d86d86578991a = "";
                        std::vector<std::string> items113 = LoopParseFunc(htCode, "\n", "\r");
                        for (size_t A_Index113 = 0; A_Index113 < items113.size() + 0; A_Index113++) {
                            std::string A_LoopField113 = items113[A_Index113 - 0];
                            //MsgBox, dsfgsdefgesrdg1
                            //MsgBox, |%A_LoopField113%|`n|%fixLoopLokingFor%|
                            if (InStr(A_LoopField113, fixLoopLokingFor) && insdeAnestedLoopBAD != 1) {
                                fixLoopLokingForNum = 1;
                                //MsgBox, do we came here 1
                            }
                            if (SubStr(Trim(A_LoopField113), 1, 4) == "for " && weAreDoneHereCurly != 1 && insdeAnestedLoopBAD != 1 && fixLoopLokingForNum == 1) {
                                s = StrSplit(A_LoopField113 ,"" + keyWordAIndex + "", 2);
                                out1z = s;
                                s = StrSplit(out1z, " ", 1);
                                out1z = Trim(s);
                                //MsgBox, % out1z
                                //MsgBox, do we came here 2
                                fixLoopLokingForNum = 0;
                                foundTheTopLoop++;
                                inTarget = 1;
                                //MsgBox, % A_LoopField113
                                dontSaveStr = 1;
                                ALoopField = A_LoopField113;
                                DeleayOneCuzOfLoopParse = 1;
                                out4758686d86d86d86578991a += ALoopField + "\n";
                            }
                            if (inTarget == 1 && InStr(A_LoopField113, Chr(123)) && insdeAnestedLoopBAD != 1) {
                                insideBracket = 1;
                            }
                            if (insideBracket == 1 && InStr(A_LoopField113, Chr(123)) && insdeAnestedLoopBAD != 1) {
                                netsedCurly++;
                            }
                            if (insideBracket == 1 && InStr(A_LoopField113, Chr(125)) && insdeAnestedLoopBAD != 1) {
                                netsedCurly--;
                                readyToEnd = 1;
                            }
                            if (SubStr(Trim(A_LoopField113), 1, 4) == "for " && insdeAnestedLoopBAD != 1 && foundTheTopLoop >= 2) {
                                insdeAnestedLoopBAD = 1;
                                insideBracket1 = 0;
                                netsedCurly1 = 0;
                            }
                            if (inTarget == 1) {
                                foundTheTopLoop++;
                            }
                            if (insdeAnestedLoopBAD == 1) {
                                if (InStr(A_LoopField113, Chr(123))) {
                                    insideBracket1 = 1;
                                }
                                if (insideBracket1 == 1 && InStr(A_LoopField113, Chr(123))) {
                                    netsedCurly1++;
                                }
                                if (insideBracket1 == 1 && InStr(A_LoopField113, Chr(125))) {
                                    netsedCurly1--;
                                    readyToEnd1 = 1;
                                }
                                if (InStr(A_LoopField113, Chr(125)) && readyToEnd1 == 1 && netsedCurly1 == 0 && insideBracket == 1) {
                                    //MsgBox, % A_LoopField113
                                    eldLoopNestedBADlol = 1;
                                }
                                out4758686d86d86d86578991a += A_LoopField113 + "\n";
                            }
                            if (inTarget == 1 && dontSaveStr != 1 && fixLoopLokingForNum != 1 && insdeAnestedLoopBAD != 1) {
                                ALoopField = A_LoopField113;
                                // Replace "A_Index" with or without a following digit with "A_Index" + out1z
                                ALoopField = RegExReplace(ALoopField, "" + keyWordAIndex + "\\d*", "" + keyWordAIndex + "" + out1z);
                                out4758686d86d86d86578991a += ALoopField + "\n";
                            }
                            if (inTarget == 1 && InStr(A_LoopField113, Chr(125)) && readyToEnd == 1 && netsedCurly == 0 && weAreDoneHereCurly == 0 && dontSaveStr != 1 && insdeAnestedLoopBAD != 1) {
                                //MsgBox, % A_LoopField113
                                weAreDoneHereCurly = 1;
                                inTarget = 0;
                                endBracketDOntPutThere = 1;
                            }
                            dontSaveStr = 0;
                            if (inTarget != 1 && endBracketDOntPutThere != 1 && insdeAnestedLoopBAD != 1) {
                                out4758686d86d86d86578991a += A_LoopField113 + "\n";
                            }
                            endBracketDOntPutThere = 0;
                            if (eldLoopNestedBADlol == 1) {
                                insdeAnestedLoopBAD = 0;
                            }
                        }
                        strstysrstsytTRIMHELP = out4758686d86d86d86578991a;
                        strstysrstsytTRIMHELP = StringTrimRight(strstysrstsytTRIMHELP, 1);
                        htCode = strstysrstsytTRIMHELP;
                        //MsgBox, % htCode
                        wasAtanyIfsElseAddAIndexLoopCurlyFix = 1;
                    } else {
                        inTarget = 0;
                        insideBracket = 0;
                        netsedCurly = 0;
                        eldLoopNestedBADlol = 0;
                        readyToEnd = 0;
                        endBracketDOntPutThere = 0;
                        dontSaveStr = 0;
                        weAreDoneHereCurly = 0;
                        DeleayOneCuzOfLoopParse = 0;
                        fixLoopLokingForNum = 0;
                        insdeAnestedLoopBAD = 0;
                        foundTheTopLoop = 0;
                        out4758686d86d86d86578991a = "";
                        std::vector<std::string> items114 = LoopParseFunc(htCode, "\n", "\r");
                        for (size_t A_Index114 = 0; A_Index114 < items114.size() + 0; A_Index114++) {
                            std::string A_LoopField114 = items114[A_Index114 - 0];
                            if (InStr(A_LoopField114 , fixLoopLokingFor) && insdeAnestedLoopBAD != 1) {
                                fixLoopLokingForNum = 1;
                                //MsgBox, do we came here 3
                            }
                            if (SubStr(Trim(A_LoopField114), 1, 4) == "for " && weAreDoneHereCurly != 1 && insdeAnestedLoopBAD != 1 && fixLoopLokingForNum == 1) {
                                s = StrSplit(A_LoopField114 ,"" + keyWordAIndex + "", 2);
                                out1z = s;
                                s = StrSplit(out1z, " ", 1);
                                out1z = Trim(s);
                                //MsgBox, % out1z
                                fixLoopLokingForNum = 0;
                                //MsgBox, do we came here 4
                                foundTheTopLoop++;
                                inTarget = 1;
                                //MsgBox, % A_LoopField114
                                dontSaveStr = 1;
                                ALoopField = A_LoopField114;
                                DeleayOneCuzOfLoopParse = 1;
                                out4758686d86d86d86578991a += ALoopField + "\n";
                            }
                            if (inTarget == 1 && InStr(A_LoopField114, Chr(123)) && insdeAnestedLoopBAD != 1) {
                                insideBracket = 1;
                            }
                            if (insideBracket == 1 && InStr(A_LoopField114, Chr(123)) && insdeAnestedLoopBAD != 1) {
                                netsedCurly++;
                            }
                            if (insideBracket == 1 && InStr(A_LoopField114, Chr(125)) && insdeAnestedLoopBAD != 1) {
                                netsedCurly--;
                                readyToEnd = 1;
                            }
                            if (SubStr(Trim(A_LoopField114), 1, 4) == "for " && insdeAnestedLoopBAD != 1 && foundTheTopLoop >= 2) {
                                insdeAnestedLoopBAD = 1;
                                insideBracket1 = 0;
                                netsedCurly1 = 0;
                            }
                            if (inTarget == 1) {
                                foundTheTopLoop++;
                            }
                            if (insdeAnestedLoopBAD == 1) {
                                if (InStr(A_LoopField114, Chr(123))) {
                                    insideBracket1 = 1;
                                }
                                if (insideBracket1 == 1 && InStr(A_LoopField114, Chr(123))) {
                                    netsedCurly1++;
                                }
                                if (insideBracket1 == 1 && InStr(A_LoopField114, Chr(125))) {
                                    netsedCurly1--;
                                    readyToEnd1 = 1;
                                }
                                if (InStr(A_LoopField114, Chr(125)) && readyToEnd1 == 1 && netsedCurly1 == 0 && insideBracket == 1) {
                                    //MsgBox, % A_LoopField114
                                    eldLoopNestedBADlol = 1;
                                }
                                out4758686d86d86d86578991a += A_LoopField114 + "\n";
                            }
                            if (inTarget == 1 && dontSaveStr != 1 && fixLoopLokingForNum != 1 && insdeAnestedLoopBAD != 1) {
                                ALoopField = A_LoopField114;
                                // Replace "A_Index" with or without a following digit with "A_Index" + out1z
                                ALoopField = RegExReplace(ALoopField, "" + keyWordAIndex + "\\d*", "" + keyWordAIndex + "" + out1z);
                                // Replace "A_Index" with or without a following digit with "A_Index" + out1z
                                ALoopField = RegExReplace(ALoopField, "" + keyWordALoopField + "\\d*", "" + keyWordALoopField + "" + out1z);
                                out4758686d86d86d86578991a += ALoopField + "\n";
                            }
                            if ((inTarget == 1 && InStr(A_LoopField114, Chr(125)) && readyToEnd == 1 && netsedCurly == 0 && weAreDoneHereCurly == 0 && dontSaveStr != 1 && insdeAnestedLoopBAD != 1)) {
                                //MsgBox, % A_LoopField114
                                weAreDoneHereCurly = 1;
                                inTarget = 0;
                                endBracketDOntPutThere = 1;
                            }
                            dontSaveStr = 0;
                            if (inTarget != 1 && endBracketDOntPutThere != 1 && insdeAnestedLoopBAD != 1) {
                                out4758686d86d86d86578991a += A_LoopField114 + "\n";
                            }
                            endBracketDOntPutThere = 0;
                            if (eldLoopNestedBADlol == 1) {
                                insdeAnestedLoopBAD = 0;
                            }
                        }
                        strstysrstsytTRIMHELP = out4758686d86d86d86578991a;
                        strstysrstsytTRIMHELP = StringTrimRight(strstysrstsytTRIMHELP, 1);
                        htCode = strstysrstsytTRIMHELP;
                        //MsgBox, % htCode
                        wasAtanyIfsElseAddAIndexLoopCurlyFix = 1;
                    }
                    if (wasAtanyIfsElseAddAIndexLoopCurlyFix == 1) {
                        AIndexLoopCurlyFix++;
                        wasAtanyIfsElseAddAIndexLoopCurlyFix = 0;
                    }
                }
                out4758686d86dgt8r754444444 = "";
                hold = 0;
                std::vector<std::string> items115 = LoopParseFunc(htCode, "\n", "\r");
                for (size_t A_Index115 = 0; A_Index115 < items115.size() + 0; A_Index115++) {
                    std::string A_LoopField115 = items115[A_Index115 - 0];
                    ignore = 0;
                    if (SubStr(Trim(A_LoopField115), 1, 4) == "for ") {
                        if (hold == 1 && holdText == A_LoopField115) {
                            ignore = 1;
                        } else {
                            holdText = A_LoopField115;
                            hold = 1;
                        }
                    }
                    if (!ignore) {
                        out4758686d86dgt8r754444444 += A_LoopField115 + "\n";
                    }
                }
                out4758686d86dgt8r754444444 = StringTrimRight(out4758686d86dgt8r754444444, 1);
                htCode = out4758686d86dgt8r754444444;
            }
            htCodeOut1234565432 = "";
            std::vector<std::string> items116 = LoopParseFunc(htCode, "\n", "\r");
            for (size_t A_Index116 = 0; A_Index116 < items116.size() + 0; A_Index116++) {
                std::string A_LoopField116 = items116[A_Index116 - 0];
                out = A_LoopField116;
                if (!InStr(out, "|itsaersdtgtgfergsdgfsegdfsedAA|")) {
                    htCodeOut1234565432 += out + "\n";
                }
            }
            htCode = StringTrimRight(htCodeOut1234565432, 1);
        }
    } else {
        htCode = code;
    }
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;
    std::string ADD_ALL_programmingBlock_HTVMsyntax = "";
    if (COUNT_programmingBlock_HTVMsyntax != 0) {
        isNotHTVMfileEXTRA_INT = 1;
        for (int A_Index117 = 0; A_Index117 < COUNT_programmingBlock_HTVMsyntax + 0; A_Index117++) {
            ADD_ALL_programmingBlock_HTVMsyntax += programmingBlock_HTVMsyntax[A_Index117] + "\n";
        }
        ADD_ALL_programmingBlock_HTVMsyntax = StringTrimRight(ADD_ALL_programmingBlock_HTVMsyntax, 1);
        ADD_ALL_programmingBlock_HTVMsyntax = compiler(ADD_ALL_programmingBlock_HTVMsyntax, allInstructionFile, "full", langToConvertToParam);
        isNotHTVMfileEXTRA_INT = 0;
        isNotHTVMfile2 = 1;
        for (int A_Index118 = 0; A_Index118 < COUNT_programmingBlock_HTVMsyntax + 0; A_Index118++) {
            htCode = StrReplace(htCode, "programmingBlock_HTVMsyntax-programmingBlock_HTVMsyntax-AA" + STR(A_Index118 + 1) + "AA", compiler(programmingBlock_HTVMsyntax[A_Index118], allInstructionFile, "full", langToConvertToParam));
        }
        isNotHTVMfile2 = 0;
    }
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;
    //;;;;;;;;;;;;;;;;;;;;;;;;;;;
    if (isNotHTVMfile == 1) {
        print("LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS");
        print("LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS");
        print("LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS");
        print("LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS");
        print("LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS");
        print("LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS");
        print("LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS");
        print("LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS");
        print("LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS");
        print("LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS");
        print("\n" + isNotHTVMfileEXTRA_LIB_INFO + "\n");
        print("Funcs needed Funcs needed Funcs needed Funcs needed Funcs needed");
        print("Funcs needed Funcs needed Funcs needed Funcs needed Funcs needed");
        print("Funcs needed Funcs needed Funcs needed Funcs needed Funcs needed");
        print("Funcs needed Funcs needed Funcs needed Funcs needed Funcs needed");
        print("Funcs needed Funcs needed Funcs needed Funcs needed Funcs needed");
        print("Funcs needed Funcs needed Funcs needed Funcs needed Funcs needed");
        print("Funcs needed Funcs needed Funcs needed Funcs needed Funcs needed");
        print("Funcs needed Funcs needed Funcs needed Funcs needed Funcs needed");
        print("Funcs needed Funcs needed Funcs needed Funcs needed Funcs needed");
        print("Funcs needed Funcs needed Funcs needed Funcs needed Funcs needed");
        print("\n" + isNotHTVMfileEXTRA_FUNCS_INFO + "\n");
        print("\n");
        print("\nYou must include all the libs from under the section and MAKE SURE your code doesn't already use them!!!");
        print("LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS LIBS");
        print("\nYou must copy-paste all the funcs from under the section and MAKE SURE your code doesn't already use them!!!");
        print("Funcs needed Funcs needed Funcs needed Funcs needed Funcs needed\n");
        print("SCROLL UP!!!!!");
        print("SCROLL UP!!!!!");
        print("SCROLL UP!!!!!");
        print("Note: If you dont see any libs or built-in functions that you need to add, then that means you dont have to!");
        return htCode;
    }
    std::string fixLuaAndRuby = "";
    if (langToConvertTo == langFileExtension_2) {
        if (useCurlyBraces_2 == "off" && useEnd_2 == "off") {
            htCode = indent_nested_curly_braces(htCode, 0);
        } else {
            htCode = indent_nested_curly_braces(htCode, 1);
        }
        if (useEnd_2 == "on") {
            std::vector<std::string> items119 = LoopParseFunc(htCode, "\n", "\r");
            for (size_t A_Index119 = 0; A_Index119 < items119.size() + 0; A_Index119++) {
                std::string A_LoopField119 = items119[A_Index119 - 0];
                if (Trim(A_LoopField119) == keyWordCurlyBraceClose_2) {
                    fixLuaAndRuby += StrReplace(A_LoopField119, keyWordCurlyBraceClose_2, Trim(keyWordEnd_2)) + "\n";
                }
                else if (SubStrLastChars(A_LoopField119, 2) == " " + keyWordCurlyBraceOpen_2) {
                    fixLuaAndRuby += StringTrimRight(A_LoopField119, 2) + "\n";
                } else {
                    fixLuaAndRuby += A_LoopField119 + "\n";
                }
            }
            htCode = StringTrimRight(fixLuaAndRuby, 1);
        }
        //;;;;;;;;;;
        //;;;;;;;;;;
    } else {
        //;;;;;;;;;;
        //;;;;;;;;;;
        if (langToConvertTo == "py" || langToConvertTo == "nim") {
            htCode = indent_nested_curly_braces(htCode, 0);
        } else {
            htCode = indent_nested_curly_braces(htCode, 1);
        }
        if (langToConvertTo == "lua" || langToConvertTo == "rb") {
            std::vector<std::string> items120 = LoopParseFunc(htCode, "\n", "\r");
            for (size_t A_Index120 = 0; A_Index120 < items120.size() + 0; A_Index120++) {
                std::string A_LoopField120 = items120[A_Index120 - 0];
                if (Trim(A_LoopField120) == "}") {
                    fixLuaAndRuby += StrReplace(A_LoopField120, "}", "end") + "\n";
                }
                else if (SubStrLastChars(A_LoopField120, 2) == " {") {
                    fixLuaAndRuby += StringTrimRight(A_LoopField120, 2) + "\n";
                } else {
                    fixLuaAndRuby += A_LoopField120 + "\n";
                }
            }
            htCode = StringTrimRight(fixLuaAndRuby, 1);
        }
    }
    std::vector<std::string> nextWordEndFix;
    std::string nextWordEndFixOut = "";
    if (langToConvertTo == "lua" || langToConvertTo == "rb") {
        std::vector<std::string> items121 = LoopParseFunc(htCode, "\n", "\r");
        for (size_t A_Index121 = 0; A_Index121 < items121.size() + 0; A_Index121++) {
            std::string A_LoopField121 = items121[A_Index121 - 0];
            nextWordEndFix.push_back(A_LoopField121);
        }
        nextWordEndFix.push_back(" ");
        std::vector<std::string> items122 = LoopParseFunc(htCode, "\n", "\r");
        for (size_t A_Index122 = 0; A_Index122 < items122.size() + 0; A_Index122++) {
            std::string A_LoopField122 = items122[A_Index122 - 0];
            if (Trim(A_LoopField122) == "end" && SubStr(Trim(nextWordEndFix[A_Index122 + 1]), 1, StrLen("elseif ")) == "elseif " || Trim(A_LoopField122) == "end" && Trim(nextWordEndFix[A_Index122 + 1]) == "else") {
                nextWordEndFixOut += "";
            } else {
                nextWordEndFixOut += A_LoopField122 + "\n";
            }
        }
        htCode = StringTrimRight(nextWordEndFixOut, 1);
    }
    std::vector<std::string> nextWordEndFixRB;
    nextWordEndFixOut = "";
    if (langToConvertTo == "rb") {
        std::vector<std::string> items123 = LoopParseFunc(htCode, "\n", "\r");
        for (size_t A_Index123 = 0; A_Index123 < items123.size() + 0; A_Index123++) {
            std::string A_LoopField123 = items123[A_Index123 - 0];
            nextWordEndFixRB.push_back(A_LoopField123);
        }
        nextWordEndFixRB.push_back(" ");
        std::vector<std::string> items124 = LoopParseFunc(htCode, "\n", "\r");
        for (size_t A_Index124 = 0; A_Index124 < items124.size() + 0; A_Index124++) {
            std::string A_LoopField124 = items124[A_Index124 - 0];
            if (Trim(A_LoopField124) == "end" && SubStr(Trim(nextWordEndFixRB[A_Index124 + 1]), 1, StrLen("rescue ")) == "rescue " || Trim(A_LoopField124) == "end" && Trim(nextWordEndFixRB[A_Index124 + 1]) == "ensure") {
                nextWordEndFixOut += "";
            } else {
                nextWordEndFixOut += A_LoopField124 + "\n";
            }
        }
        htCode = StringTrimRight(nextWordEndFixOut, 1);
    }
    if (langToConvertTo == "go") {
        std::vector<std::string> fixGoManGoIsSoAnnoyingBroooFurure;
        std::vector<std::string> items125 = LoopParseFunc(htCode, "\n", "\r");
        for (size_t A_Index125 = 0; A_Index125 < items125.size() + 0; A_Index125++) {
            std::string A_LoopField125 = items125[A_Index125 - 0];
            fixGoManGoIsSoAnnoyingBroooFurure.push_back(A_LoopField125);
        }
        fixGoManGoIsSoAnnoyingBroooFurure.push_back(" ");
        int fixGoManGoIsSoAnnoyingBroooSkip = 0;
        int fixGoManGoIsSoAnnoyingBroooCount = 0;
        std::string fixGoManGoIsSoAnnoyingBroooCountSpaceses = "";
        std::string fixGoManGoIsSoAnnoyingBrooo = "";
        std::vector<std::string> items126 = LoopParseFunc(htCode, "\n", "\r");
        for (size_t A_Index126 = 0; A_Index126 < items126.size() + 0; A_Index126++) {
            std::string A_LoopField126 = items126[A_Index126 - 0];
            if (Trim(A_LoopField126) == "}" && SubStr(Trim(fixGoManGoIsSoAnnoyingBroooFurure[A_Index126 + 1]), 1, StrLen("else if ")) == "else if ") {
                fixGoManGoIsSoAnnoyingBroooSkip = 1;
                fixGoManGoIsSoAnnoyingBroooCount = 0;
                std::vector<std::string> items127 = LoopParseFunc(fixGoManGoIsSoAnnoyingBroooFurure[A_Index126 + 1]);
                for (size_t A_Index127 = 0; A_Index127 < items127.size() + 0; A_Index127++) {
                    std::string A_LoopField127 = items127[A_Index127 - 0];
                    if (A_LoopField127 == " ") {
                        fixGoManGoIsSoAnnoyingBroooCount++;
                    } else {
                        break;
                    }
                }
                fixGoManGoIsSoAnnoyingBroooCountSpaceses = "";
                for (int A_Index128 = 0; A_Index128 < fixGoManGoIsSoAnnoyingBroooCount + 0; A_Index128++) {
                    fixGoManGoIsSoAnnoyingBroooCountSpaceses += " ";
                }
                fixGoManGoIsSoAnnoyingBrooo += fixGoManGoIsSoAnnoyingBroooCountSpaceses + "} " + Trim(fixGoManGoIsSoAnnoyingBroooFurure[A_Index126 + 1]) + "\n";
            } else {
                if (fixGoManGoIsSoAnnoyingBroooSkip == 0) {
                    fixGoManGoIsSoAnnoyingBrooo += A_LoopField126 + "\n";
                }
                fixGoManGoIsSoAnnoyingBroooSkip = 0;
            }
        }
        htCode = StringTrimRight(fixGoManGoIsSoAnnoyingBrooo, 1);
    }
    if (COUNT_programmingBlock_InTheTranspiledLang != 0) {
        for (int A_Index129 = 0; A_Index129 < COUNT_programmingBlock_InTheTranspiledLang + 0; A_Index129++) {
            htCode = StrReplace(htCode, "programmingBlock_InTheTranspiledLang-programmingBlock_InTheTranspiledLang-AA" + STR(A_Index129 + 1) + "AA", programmingBlock_InTheTranspiledLang[A_Index129]);
        }
    }
    if (langToConvertTo == "cpp") {
        if (COUNT_programmingBlock_CPP != 0) {
            for (int A_Index130 = 0; A_Index130 < COUNT_programmingBlock_CPP + 0; A_Index130++) {
                htCode = StrReplace(htCode, "programmingBlock_CPP-programmingBlock_CPP-AA" + STR(A_Index130 + 1) + "AA", programmingBlock_CPP[A_Index130]);
            }
        }
    } else {
        if (COUNT_programmingBlock_CPP != 0) {
            for (int A_Index131 = 0; A_Index131 < COUNT_programmingBlock_CPP + 0; A_Index131++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_CPP-programmingBlock_CPP-AA" + STR(A_Index131 + 1) + "AA", keyWordCodeInTheTranspiledLangStartCPP + "\n" + programmingBlock_CPP[A_Index131] + "\n" + keyWordCodeInTheTranspiledLangEndCPP);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_CPP-programmingBlock_CPP-AA" + STR(A_Index131 + 1) + "AA", "\n");
                }
            }
        }
    }
    if (langToConvertTo == "py") {
        if (COUNT_programmingBlock_PY != 0) {
            for (int A_Index132 = 0; A_Index132 < COUNT_programmingBlock_PY + 0; A_Index132++) {
                htCode = StrReplace(htCode, "programmingBlock_PY-programmingBlock_PY-AA" + STR(A_Index132 + 1) + "AA", programmingBlock_PY[A_Index132]);
            }
        }
    } else {
        if (COUNT_programmingBlock_PY != 0) {
            for (int A_Index133 = 0; A_Index133 < COUNT_programmingBlock_PY + 0; A_Index133++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_PY-programmingBlock_PY-AA" + STR(A_Index133 + 1) + "AA", keyWordCodeInTheTranspiledLangStartPY + "\n" + programmingBlock_PY[A_Index133] + "\n" + keyWordCodeInTheTranspiledLangEndPY);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_PY-programmingBlock_PY-AA" + STR(A_Index133 + 1) + "AA", "\n");
                }
            }
        }
    }
    if (langToConvertTo == "js") {
        if (COUNT_programmingBlock_JS != 0) {
            for (int A_Index134 = 0; A_Index134 < COUNT_programmingBlock_JS + 0; A_Index134++) {
                htCode = StrReplace(htCode, "programmingBlock_JS-programmingBlock_JS-AA" + STR(A_Index134 + 1) + "AA", programmingBlock_JS[A_Index134]);
            }
        }
    } else {
        if (COUNT_programmingBlock_JS != 0) {
            for (int A_Index135 = 0; A_Index135 < COUNT_programmingBlock_JS + 0; A_Index135++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_JS-programmingBlock_JS-AA" + STR(A_Index135 + 1) + "AA", keyWordCodeInTheTranspiledLangStartJS + "\n" + programmingBlock_JS[A_Index135] + "\n" + keyWordCodeInTheTranspiledLangEndJS);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_JS-programmingBlock_JS-AA" + STR(A_Index135 + 1) + "AA", "\n");
                }
            }
        }
    }
    if (langToConvertTo == "go") {
        if (COUNT_programmingBlock_GO != 0) {
            for (int A_Index136 = 0; A_Index136 < COUNT_programmingBlock_GO + 0; A_Index136++) {
                htCode = StrReplace(htCode, "programmingBlock_GO-programmingBlock_GO-AA" + STR(A_Index136 + 1) + "AA", programmingBlock_GO[A_Index136]);
            }
        }
    } else {
        if (COUNT_programmingBlock_GO != 0) {
            for (int A_Index137 = 0; A_Index137 < COUNT_programmingBlock_GO + 0; A_Index137++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_GO-programmingBlock_GO-AA" + STR(A_Index137 + 1) + "AA", keyWordCodeInTheTranspiledLangStartGO + "\n" + programmingBlock_GO[A_Index137] + "\n" + keyWordCodeInTheTranspiledLangEndGO);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_GO-programmingBlock_GO-AA" + STR(A_Index137 + 1) + "AA", "\n");
                }
            }
        }
    }
    if (langToConvertTo == "lua") {
        if (COUNT_programmingBlock_LUA != 0) {
            for (int A_Index138 = 0; A_Index138 < COUNT_programmingBlock_LUA + 0; A_Index138++) {
                htCode = StrReplace(htCode, "programmingBlock_LUA-programmingBlock_LUA-AA" + STR(A_Index138 + 1) + "AA", programmingBlock_LUA[A_Index138]);
            }
        }
    } else {
        if (COUNT_programmingBlock_LUA != 0) {
            for (int A_Index139 = 0; A_Index139 < COUNT_programmingBlock_LUA + 0; A_Index139++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_LUA-programmingBlock_LUA-AA" + STR(A_Index139 + 1) + "AA", keyWordCodeInTheTranspiledLangStartLUA + "\n" + programmingBlock_LUA[A_Index139] + "\n" + keyWordCodeInTheTranspiledLangEndLUA);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_LUA-programmingBlock_LUA-AA" + STR(A_Index139 + 1) + "AA", "\n");
                }
            }
        }
    }
    if (langToConvertTo == "cs") {
        if (COUNT_programmingBlock_CS != 0) {
            for (int A_Index140 = 0; A_Index140 < COUNT_programmingBlock_CS + 0; A_Index140++) {
                htCode = StrReplace(htCode, "programmingBlock_CS-programmingBlock_CS-AA" + STR(A_Index140 + 1) + "AA", programmingBlock_CS[A_Index140]);
            }
        }
    } else {
        if (COUNT_programmingBlock_CS != 0) {
            for (int A_Index141 = 0; A_Index141 < COUNT_programmingBlock_CS + 0; A_Index141++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_CS-programmingBlock_CS-AA" + STR(A_Index141 + 1) + "AA", keyWordCodeInTheTranspiledLangStartCS + "\n" + programmingBlock_CS[A_Index141] + "\n" + keyWordCodeInTheTranspiledLangEndCS);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_CS-programmingBlock_CS-AA" + STR(A_Index141 + 1) + "AA", "\n");
                }
            }
        }
    }
    if (langToConvertTo == "java") {
        if (COUNT_programmingBlock_JAVA != 0) {
            for (int A_Index142 = 0; A_Index142 < COUNT_programmingBlock_JAVA + 0; A_Index142++) {
                htCode = StrReplace(htCode, "programmingBlock_JAVA-programmingBlock_JAVA-AA" + STR(A_Index142 + 1) + "AA", programmingBlock_JAVA[A_Index142]);
            }
        }
    } else {
        if (COUNT_programmingBlock_JAVA != 0) {
            for (int A_Index143 = 0; A_Index143 < COUNT_programmingBlock_JAVA + 0; A_Index143++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_JAVA-programmingBlock_JAVA-AA" + STR(A_Index143 + 1) + "AA", keyWordCodeInTheTranspiledLangStartJAVA + "\n" + programmingBlock_JAVA[A_Index143] + "\n" + keyWordCodeInTheTranspiledLangEndJAVA);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_JAVA-programmingBlock_JAVA-AA" + STR(A_Index143 + 1) + "AA", "\n");
                }
            }
        }
    }
    if (langToConvertTo == "kt") {
        if (COUNT_programmingBlock_KT != 0) {
            for (int A_Index144 = 0; A_Index144 < COUNT_programmingBlock_KT + 0; A_Index144++) {
                htCode = StrReplace(htCode, "programmingBlock_KT-programmingBlock_KT-AA" + STR(A_Index144 + 1) + "AA", programmingBlock_KT[A_Index144]);
            }
        }
    } else {
        if (COUNT_programmingBlock_KT != 0) {
            for (int A_Index145 = 0; A_Index145 < COUNT_programmingBlock_KT + 0; A_Index145++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_KT-programmingBlock_KT-AA" + STR(A_Index145 + 1) + "AA", keyWordCodeInTheTranspiledLangStartKT + "\n" + programmingBlock_KT[A_Index145] + "\n" + keyWordCodeInTheTranspiledLangEndKT);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_KT-programmingBlock_KT-AA" + STR(A_Index145 + 1) + "AA", "\n");
                }
            }
        }
    }
    if (langToConvertTo == "rb") {
        if (COUNT_programmingBlock_RB != 0) {
            for (int A_Index146 = 0; A_Index146 < COUNT_programmingBlock_RB + 0; A_Index146++) {
                htCode = StrReplace(htCode, "programmingBlock_RB-programmingBlock_RB-AA" + STR(A_Index146 + 1) + "AA", programmingBlock_RB[A_Index146]);
            }
        }
    } else {
        if (COUNT_programmingBlock_RB != 0) {
            for (int A_Index147 = 0; A_Index147 < COUNT_programmingBlock_RB + 0; A_Index147++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_RB-programmingBlock_RB-AA" + STR(A_Index147 + 1) + "AA", keyWordCodeInTheTranspiledLangStartRB + "\n" + programmingBlock_RB[A_Index147] + "\n" + keyWordCodeInTheTranspiledLangEndRB);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_RB-programmingBlock_RB-AA" + STR(A_Index147 + 1) + "AA", "\n");
                }
            }
        }
    }
    if (langToConvertTo == "nim") {
        if (COUNT_programmingBlock_NIM != 0) {
            for (int A_Index148 = 0; A_Index148 < COUNT_programmingBlock_NIM + 0; A_Index148++) {
                htCode = StrReplace(htCode, "programmingBlock_NIM-programmingBlock_NIM-AA" + STR(A_Index148 + 1) + "AA", programmingBlock_NIM[A_Index148]);
            }
        }
    } else {
        if (COUNT_programmingBlock_NIM != 0) {
            for (int A_Index149 = 0; A_Index149 < COUNT_programmingBlock_NIM + 0; A_Index149++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_NIM-programmingBlock_NIM-AA" + STR(A_Index149 + 1) + "AA", keyWordCodeInTheTranspiledLangStartNIM + "\n" + programmingBlock_NIM[A_Index149] + "\n" + keyWordCodeInTheTranspiledLangEndNIM);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_NIM-programmingBlock_NIM-AA" + STR(A_Index149 + 1) + "AA", "\n");
                }
            }
        }
    }
    if (langToConvertTo == "ahk") {
        if (COUNT_programmingBlock_AHK != 0) {
            for (int A_Index150 = 0; A_Index150 < COUNT_programmingBlock_AHK + 0; A_Index150++) {
                htCode = StrReplace(htCode, "programmingBlock_AHK-programmingBlock_AHK-AA" + STR(A_Index150 + 1) + "AA", programmingBlock_AHK[A_Index150]);
            }
        }
    } else {
        if (COUNT_programmingBlock_AHK != 0) {
            for (int A_Index151 = 0; A_Index151 < COUNT_programmingBlock_AHK + 0; A_Index151++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_AHK-programmingBlock_AHK-AA" + STR(A_Index151 + 1) + "AA", keyWordCodeInTheTranspiledLangStartAHK + "\n" + programmingBlock_AHK[A_Index151] + "\n" + keyWordCodeInTheTranspiledLangEndAHK);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_AHK-programmingBlock_AHK-AA" + STR(A_Index151 + 1) + "AA", "\n");
                }
            }
        }
    }
    if (langToConvertTo == "swift") {
        if (COUNT_programmingBlock_SWIFT != 0) {
            for (int A_Index152 = 0; A_Index152 < COUNT_programmingBlock_SWIFT + 0; A_Index152++) {
                htCode = StrReplace(htCode, "programmingBlock_SWIFT-programmingBlock_SWIFT-AA" + STR(A_Index152 + 1) + "AA", programmingBlock_SWIFT[A_Index152]);
            }
        }
    } else {
        if (COUNT_programmingBlock_SWIFT != 0) {
            for (int A_Index153 = 0; A_Index153 < COUNT_programmingBlock_SWIFT + 0; A_Index153++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_SWIFT-programmingBlock_SWIFT-AA" + STR(A_Index153 + 1) + "AA", keyWordCodeInTheTranspiledLangStartSWIFT + "\n" + programmingBlock_SWIFT[A_Index153] + "\n" + keyWordCodeInTheTranspiledLangEndSWIFT);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_SWIFT-programmingBlock_SWIFT-AA" + STR(A_Index153 + 1) + "AA", "\n");
                }
            }
        }
    }
    if (langToConvertTo == "dart") {
        if (COUNT_programmingBlock_DART != 0) {
            for (int A_Index154 = 0; A_Index154 < COUNT_programmingBlock_DART + 0; A_Index154++) {
                htCode = StrReplace(htCode, "programmingBlock_DART-programmingBlock_DART-AA" + STR(A_Index154 + 1) + "AA", programmingBlock_DART[A_Index154]);
            }
        }
    } else {
        if (COUNT_programmingBlock_DART != 0) {
            for (int A_Index155 = 0; A_Index155 < COUNT_programmingBlock_DART + 0; A_Index155++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_DART-programmingBlock_DART-AA" + STR(A_Index155 + 1) + "AA", keyWordCodeInTheTranspiledLangStartDART + "\n" + programmingBlock_DART[A_Index155] + "\n" + keyWordCodeInTheTranspiledLangEndDART);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_DART-programmingBlock_DART-AA" + STR(A_Index155 + 1) + "AA", "\n");
                }
            }
        }
    }
    if (langToConvertTo == "ts") {
        if (COUNT_programmingBlock_TS != 0) {
            for (int A_Index156 = 0; A_Index156 < COUNT_programmingBlock_TS + 0; A_Index156++) {
                htCode = StrReplace(htCode, "programmingBlock_TS-programmingBlock_TS-AA" + STR(A_Index156 + 1) + "AA", programmingBlock_TS[A_Index156]);
            }
        }
    } else {
        if (COUNT_programmingBlock_TS != 0) {
            for (int A_Index157 = 0; A_Index157 < COUNT_programmingBlock_TS + 0; A_Index157++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_TS-programmingBlock_TS-AA" + STR(A_Index157 + 1) + "AA", keyWordCodeInTheTranspiledLangStartTS + "\n" + programmingBlock_TS[A_Index157] + "\n" + keyWordCodeInTheTranspiledLangEndTS);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_TS-programmingBlock_TS-AA" + STR(A_Index157 + 1) + "AA", "\n");
                }
            }
        }
    }
    if (langToConvertTo == "groovy") {
        if (COUNT_programmingBlock_GROOVY != 0) {
            for (int A_Index158 = 0; A_Index158 < COUNT_programmingBlock_GROOVY + 0; A_Index158++) {
                htCode = StrReplace(htCode, "programmingBlock_GROOVY-programmingBlock_GROOVY-AA" + STR(A_Index158 + 1) + "AA", programmingBlock_GROOVY[A_Index158]);
            }
        }
    } else {
        if (COUNT_programmingBlock_GROOVY != 0) {
            for (int A_Index159 = 0; A_Index159 < COUNT_programmingBlock_GROOVY + 0; A_Index159++) {
                if (langToConvertTo == langFileExtension_2) {
                    htCode = StrReplace(htCode, "programmingBlock_GROOVY-programmingBlock_GROOVY-AA" + STR(A_Index159 + 1) + "AA", keyWordCodeInTheTranspiledLangStartGROOVY + "\n" + programmingBlock_GROOVY[A_Index159] + "\n" + keyWordCodeInTheTranspiledLangEndGROOVY);
                } else {
                    htCode = StrReplace(htCode, "programmingBlock_GROOVY-programmingBlock_GROOVY-AA" + STR(A_Index159 + 1) + "AA", "\n");
                }
            }
        }
    }
    //;;;;;;;;;;
    if (langToConvertTo == langFileExtension_2) {
        if (COUNT_programmingBlock_HTVM != 0) {
            for (int A_Index160 = 0; A_Index160 < COUNT_programmingBlock_HTVM + 0; A_Index160++) {
                htCode = StrReplace(htCode, "programmingBlock_HTVM-programmingBlock_HTVM-AA" + STR(A_Index160 + 1) + "AA", programmingBlock_HTVM[A_Index160]);
            }
        }
    } else {
        if (COUNT_programmingBlock_HTVM != 0) {
            for (int A_Index161 = 0; A_Index161 < COUNT_programmingBlock_HTVM + 0; A_Index161++) {
                htCode = StrReplace(htCode, "programmingBlock_HTVM-programmingBlock_HTVM-AA" + STR(A_Index161 + 1) + "AA", "\n");
            }
        }
    }
    areWeInAFuncFromInstructions = 0;
    areWeInAFuncFromInstructionsLineNum = 0;
    std::string funcLangHolder = "";
    std::string funcNameHolder = "";
    std::string funcLibsHolder = "";
    std::string funcFuncHolder = "";
    std::string funcDescriptionHolder = "";
    std::vector<std::string> allFuncLang;
    std::vector<std::string> allFuncNames;
    std::vector<std::string> allFuncLibs;
    std::vector<std::string> allFuncs;
    std::vector<std::string> allfuncDescription;
    int correctLang = 0;
    std::vector<std::string> items162 = LoopParseFunc(instructions, "\n", "\r");
    for (size_t A_Index162 = 0; A_Index162 < items162.size() + 0; A_Index162++) {
        std::string A_LoopField162 = items162[A_Index162 - 0];
        if (Trim(A_LoopField162) == "funcEND======================funcEND==============") {
            areWeInAFuncFromInstructions = 0;
            areWeInAFuncFromInstructionsLineNum = 0;
            if (correctLang == 1 && InStr(htCode, Trim(funcNameHolder))) {
                //MsgBox, % funcFuncHolder
                allFuncs.push_back(funcFuncHolder);
            }
            correctLang = 0;
            funcFuncHolder = "";
        }
        if (areWeInAFuncFromInstructions == 1) {
            if (areWeInAFuncFromInstructionsLineNum == 1) {
                // name of the func
                funcLangHolder = StringTrimLeft(A_LoopField162, 5);
                if (Trim(funcLangHolder) == langToConvertTo) {
                    allFuncLang.push_back(Trim(funcLangHolder));
                    correctLang = 1;
                }
            }
            if (areWeInAFuncFromInstructionsLineNum == 2) {
                // name of the func
                funcNameHolder = StringTrimLeft(A_LoopField162, 5);
                if (correctLang == 1 && InStr(htCode, Trim(funcNameHolder))) {
                    allFuncNames.push_back(Trim(funcNameHolder));
                }
            }
            if (areWeInAFuncFromInstructionsLineNum == 3) {
                // all libs
                funcLibsHolder = StringTrimLeft(A_LoopField162, 5);
                if (correctLang == 1 && InStr(htCode, Trim(funcNameHolder))) {
                    allFuncLibs.push_back(Trim(funcLibsHolder));
                }
            }
            if (areWeInAFuncFromInstructionsLineNum == 4) {
                // func description
                funcDescriptionHolder = StringTrimLeft(A_LoopField162, 12);
                if (correctLang == 1 && InStr(htCode, Trim(funcNameHolder))) {
                    allfuncDescription.push_back(Trim(funcDescriptionHolder));
                }
            }
            if (areWeInAFuncFromInstructionsLineNum >= 5) {
                // the full func
                if (correctLang == 1 && InStr(htCode, Trim(funcNameHolder))) {
                    funcFuncHolder += A_LoopField162 + "\n";
                }
            }
            //MsgBox, % A_LoopField162
            areWeInAFuncFromInstructionsLineNum++;
        }
        if (Trim(A_LoopField162) == "func======================func==============") {
            areWeInAFuncFromInstructions = 1;
            areWeInAFuncFromInstructionsLineNum = 1;
            correctLang = 0;
        }
    }
    //~ MsgBox, ===========================================================================
    //~ msgbox, % allFuncNames
    //~ MsgBox, ===========================================================================
    //~ msgbox, % allFuncLibs
    //~ MsgBox, ===========================================================================
    //~ msgbox, % allFuncLang
    //~ MsgBox, ===========================================================================
    //~ msgbox, % allFuncs
    //~ MsgBox, ===========================================================================
    if (isNotHTVMfile2 == 0) {
        if (langToConvertTo == "cpp") {
            htCode = htCode + "\n    return 0;\n}";
            htCode = StrReplace(htCode, "int main(int argc, char* argv[]);", "int main(int argc, char* argv[])");
        }
        if (langToConvertTo == "js" && useJavaScriptAmainFuncDef == "on") {
            htCode = htCode + "\n}\nmain();";
            htCode = StrReplace(htCode, "async function main();", "async function main()");
            htCode = StrReplace(htCode, "function async function main()", "async function main()");
        }
        if (langToConvertTo == "ts" && useJavaScriptAmainFuncDef == "on") {
            htCode = htCode + "\n}\nmain();";
            htCode = StrReplace(htCode, "async function main(): Promise<void>;", "async function main(): Promise<void>");
            htCode = StrReplace(htCode, "function async function main(): Promise<void>", "async function main(): Promise<void>");
        }
        if (langToConvertTo == "go") {
            htCode = htCode + "\n}";
            htCode = StrReplace(htCode, "func main();", "func main()");
        }
        if (langToConvertTo == "cs") {
            htCode = htCode + Chr(10) + "}" + Chr(10) + "}";
            htCode = StrReplace(htCode, "static void Main(string[] args);", "static void Main(string[] args)");
        }
        if (langToConvertTo == "java") {
            htCode = htCode + Chr(10) + "}" + Chr(10) + "}";
            htCode = StrReplace(htCode, "public static void main(String[] args);", "public static void main(String[] args)");
        }
        if (langToConvertTo == "kt") {
            htCode = htCode + "\n}";
            htCode = StrReplace(htCode, "fun main(args: Array<String>);", "fun main(args: Array<String>)");
        }
        if (langToConvertTo == "swift") {
            htCode = htCode + "\n}\nmain()";
            htCode = StrReplace(htCode, "func main();", "func main()");
            htCode = StrReplace(htCode, "func main() ->", "func main()");
        }
        if (langToConvertTo == "dart") {
            htCode = htCode + "\n}";
            htCode = StrReplace(htCode, "void main(List<String> arguments);", "void main(List<String> arguments)");
        }
    }
    std::string jsHTMLdownCode = "</script>\n</body>\n</html>";
    int includeLibsInCppIf = 0;
    std::string allFuncsToPutAtTop = Chr(10);
    std::string allLibsToPutAtTop = "";
    if (!(allFuncNames.size() <= 0)) {
        for (int A_Index163 = 0; A_Index163 < allFuncNames.size() + 0; A_Index163++) {
            if (InStr(htCode, allFuncNames[A_Index163]) + "(") {
                //MsgBox, % allFuncNames[A_Index163]
                allFuncsToPutAtTop += allFuncs[A_Index163] + "\n";
                if (Trim(allFuncLibs[A_Index163]) != "null") {
                    allLibsToPutAtTop += allFuncLibs[A_Index163] + "|";
                }
            }
        }
        allLibsToPutAtTop = StringTrimRight(allLibsToPutAtTop, 1);
        std::string allLibsToPutAtTopTEMP;
        std::vector<std::string> items164 = LoopParseFunc(allLibsToPutAtTop, "|");
        for (size_t A_Index164 = 0; A_Index164 < items164.size() + 0; A_Index164++) {
            std::string A_LoopField164 = items164[A_Index164 - 0];
            allLibsToPutAtTopTEMP += A_LoopField164 + "\n";
        }
        allLibsToPutAtTop = StringTrimRight(allLibsToPutAtTopTEMP, 1);
        includeLibsInCppIf = 1;
        if (langToConvertTo == "cpp") {
            allLibsToPutAtTop = "#include <iostream>\n#include <sstream>\n#include <string>\n#include <cstdint>\n#include <algorithm>\n#include <vector>\n#include <any>\n#include <optional>\n" + allLibsToPutAtTop;
        }
        if (langToConvertTo == "cs") {
            allLibsToPutAtTop = "using System;\n" + allLibsToPutAtTop;
        }
        allLibsToPutAtTop = Sort(allLibsToPutAtTop, "U");
        allLibsToPutAtTop = StrReplace(allLibsToPutAtTop, "~~~", "\n");
        if (isNotHTVMfileEXTRA_INT == 1) {
            isNotHTVMfileEXTRA_LIB_INFO = allLibsToPutAtTop;
            isNotHTVMfileEXTRA_FUNCS_INFO = allFuncsToPutAtTop;
        }
        if (isNotHTVMfile2 == 0) {
            if (langToConvertTo == "cs" || langToConvertTo == "java") {
                htCode = "\n" + allFuncsToPutAtTop + "\n" + htCode;
            } else {
                if (langToConvertTo != "js") {
                    htCode = allLibsToPutAtTop + "\n" + allFuncsToPutAtTop + "\n" + htCode;
                } else {
                    if (useJavaScriptInAfullHTMLfile != "on") {
                        htCode = allLibsToPutAtTop + "\n" + allFuncsToPutAtTop + "\n" + htCode;
                    } else {
                        htCode = "\n" + allFuncsToPutAtTop + "\n" + htCode;
                    }
                }
            }
        }
        if (langToConvertTo == "cs") {
            htCode = allLibsToPutAtTop + "\nclass Program\n{\n" + htCode;
        }
        if (langToConvertTo == "java") {
            htCode = allLibsToPutAtTop + "\npublic class Main\n{\n" + htCode;
        }
        if (langToConvertTo == "go") {
            htCode = "package main\nimport (\n" + htCode;
        }
    }
    for (int A_Index165 = 0; A_Index165 < theIdNumOfThe34 + 0; A_Index165++) {
        if (theIdNumOfThe34 == A_Index165 + 1) {
            if (langToConvertTo == langFileExtension_2) {
                if (keyWordEscpaeChar_2 == "\\" && keyWordEscpaeChar != "\\") {
                    htCode = StrReplace(htCode, "ihuiuuhuuhtheidFor--asdsas--theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(A_Index165 + 1) + Chr(65) + Chr(65), StrReplace(StrReplace(theIdNumOfThe34theVar[A_Index165 + 1], "\\", "\\\\"), keyWordEscpaeChar, keyWordEscpaeChar_2) + Chr(34));
                } else {
                    htCode = StrReplace(htCode, "ihuiuuhuuhtheidFor--asdsas--theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(A_Index165 + 1) + Chr(65) + Chr(65), StrReplace(theIdNumOfThe34theVar[A_Index165 + 1], keyWordEscpaeChar, keyWordEscpaeChar_2) + Chr(34));
                }
            } else {
                htCode = StrReplace(htCode, "ihuiuuhuuhtheidFor--asdsas--theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(A_Index165 + 1) + Chr(65) + Chr(65), theIdNumOfThe34theVar[A_Index165 + 1] + Chr(34));
            }
        } else {
            if (langToConvertTo == langFileExtension_2) {
                if (keyWordEscpaeChar_2 == "\\" && keyWordEscpaeChar != "\\") {
                    htCode = StrReplace(htCode, "ihuiuuhuuhtheidFor--asdsas--theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(A_Index165 + 1) + Chr(65) + Chr(65), StrReplace(StrReplace(theIdNumOfThe34theVar[A_Index165 + 1], "\\", "\\\\"), keyWordEscpaeChar, keyWordEscpaeChar_2));
                } else {
                    htCode = StrReplace(htCode, "ihuiuuhuuhtheidFor--asdsas--theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(A_Index165 + 1) + Chr(65) + Chr(65), StrReplace(theIdNumOfThe34theVar[A_Index165 + 1], keyWordEscpaeChar, keyWordEscpaeChar_2));
                }
            } else {
                htCode = StrReplace(htCode, "ihuiuuhuuhtheidFor--asdsas--theuhturtyphoutr--" + Chr(65) + Chr(65) + STR(A_Index165 + 1) + Chr(65) + Chr(65), theIdNumOfThe34theVar[A_Index165 + 1]);
            }
        }
    }
    if (langToConvertTo == langFileExtension_2) {
        htCode = StrReplace(htCode, ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes, keyWordEscpaeChar_2 + Chr(34));
    } else {
        htCode = StrReplace(htCode, ReplaceFixWhitOutFixDoubleQuotesInsideDoubleQuotes, Chr(92) + Chr(34));
    }
    htCode = StrReplace(htCode, "std::string(" + Chr(34) + Chr(34) + ";),", "std::string(" + Chr(34) + Chr(34) + "),");
    std::string jsHTMLupCode = "<!doctype html>\n<html lang=" + Chr(34) + "en" + Chr(34) + ">\n    <head>\n        <meta charset=" + Chr(34) + "UTF-8" + Chr(34) + " />\n        <meta name=" + Chr(34) + "viewport" + Chr(34) + " content=" + Chr(34) + "width=device-width, initial-scale=1.0" + Chr(34) + " />\n        <title>HTVM</title>\n        <style>\n            body {\n                background-color: #202020;\n                font-family:\n                    " + Chr(34) + "Open Sans" + Chr(34) + ",\n                    -apple-system,\n                    BlinkMacSystemFont,\n                    " + Chr(34) + "Segoe UI" + Chr(34) + ",\n                    Roboto,\n                    Oxygen-Sans,\n                    Ubuntu,\n                    Cantarell,\n                    " + Chr(34) + "Helvetica Neue" + Chr(34) + ",\n                    Helvetica,\n                    Arial,\n                    sans-serif;\n            }\n        </style>\n" + allLibsToPutAtTop + "\n</head>\n    <body>\n<script>";
    if (isNotHTVMfile2 == 0) {
        if (useJavaScriptInAfullHTMLfile == "on" && langToConvertTo == "js") {
            htCode = jsHTMLupCode + "\n" + htCode + "\n" + jsHTMLdownCode;
        }
        if (langToConvertTo == "cpp" && includeLibsInCppIf == 0) {
            htCode = "#include <iostream>\n#include <sstream>\n#include <any>\n#include <string>\n#include <cstdint>\n#include <algorithm>\n#include <vector>\n\n" + htCode;
        }
        if (langToConvertTo == "cs") {
            htCode = "\n" + htCode;
        }
        if (langToConvertTo == "ahk") {
            htCode = "#EscapeChar \\\n" + htCode;
        }
        if (langToConvertTo == "swift") {
            htCode = "import Foundation\n" + htCode;
        }
        if (langToConvertTo == langFileExtension_2) {
            if (SubStr(htCode, 1, 1) == "\n") {
                htCode = StringTrimLeft(htCode, 1);
            }
        }
    }
    print(htCode);
    return htCode;
}
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
//;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
void HTVMv2() {
    std::string argCODE = "";
    std::string argCODEfile = "";
    std::string argHTVMinstr = "";
    std::string argLangTo = "";
    std::string OUTCODE = "null";
    int numOfParams = 0;
    HTVM_v2_HTVM();
    if (noParams == true) {
        return;
    }
    std::vector<std::string> items166 = LoopParseFunc(str0);
    for (size_t A_Index166 = 0; A_Index166 < items166.size() + 0; A_Index166++) {
        std::string A_LoopField166 = items166[A_Index166 - 0];
        str00 = Trim(A_LoopField166);
        str00 = StringTrimRight(str00, 1);
    }
    print("HTVM v2");
    if (HTVM_getLang_HTVM() == "cpp" || HTVM_getLang_HTVM() == "py") {
        if (HTVM_getLang_HTVM() == "cpp") {
            print("CPP");
        }
        if (HTVM_getLang_HTVM() == "py") {
            print("PY");
        }
        std::vector<std::string> items167 = LoopParseFunc(allArgs, "\n", "\r");
        for (size_t A_Index167 = 0; A_Index167 < items167.size() + 0; A_Index167++) {
            std::string A_LoopField167 = items167[A_Index167 - 0];
            if (A_Index167 == 0) {
                numOfParams++;
                argCODE = FileRead(Trim(A_LoopField167));
                argCODEfile = Trim(A_LoopField167);
            }
            else if (A_Index167 == 1) {
                numOfParams++;
                argHTVMinstr = Trim(A_LoopField167);
            }
            else if (A_Index167 == 2) {
                numOfParams++;
                argLangTo = Trim(A_LoopField167);
            } else {
                numOfParams++;
                argHTVMinstrMORE.push_back(Trim(A_LoopField167));
            }
        }
        print("===============123431234===========start=====");
        for (int A_Index168 = 0; A_Index168 < argHTVMinstrMORE.size() + 0; A_Index168++) {
            print(argHTVMinstrMORE[A_Index168]);
        }
        print("===============123431234==========end======");
        print(StringTrimRight(argCODEfile, StrLen(langFileExtension)) + langToConvertTo);
        if (SubStrLastChars(argCODEfile, 4) == ".cpp" || SubStrLastChars(argCODEfile, 3) == ".py" || SubStrLastChars(argCODEfile, 3) == ".js" || SubStrLastChars(argCODEfile, 3) == ".go" || SubStrLastChars(argCODEfile, 4) == ".lua" || SubStrLastChars(argCODEfile, 3) == ".cs" || SubStrLastChars(argCODEfile, 5) == ".java" || SubStrLastChars(argCODEfile, 3) == ".kt" || SubStrLastChars(argCODEfile, 3) == ".rb" || SubStrLastChars(argCODEfile, 4) == ".nim" || SubStrLastChars(argCODEfile, 4) == ".ahk" || SubStrLastChars(argCODEfile, 6) == ".swift" || SubStrLastChars(argCODEfile, 5) == ".dart" || SubStrLastChars(argCODEfile, 3) == ".ts" || SubStrLastChars(argCODEfile, 7) == ".groovy" || SubStrLastChars(argCODEfile, StrLen("." + Trim(StrSplit(StrReplace(FileRead(argHTVMinstr), Chr(13), ""), "\n", 2)))) == "." + Trim(StrSplit(StrReplace(FileRead(argHTVMinstr), Chr(13), ""), "\n", 2)) && numOfParams == 2) {
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            if (SubStrLastChars(argCODEfile, 4) == ".cpp") {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "cpp");
                FileDelete(Trim(argCODEfile));
                FileAppend(OUTCODE, Trim(argCODEfile));
                return;
            }
            else if (SubStrLastChars(argCODEfile, 3) == ".py") {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "py");
                FileDelete(Trim(argCODEfile));
                FileAppend(OUTCODE, Trim(argCODEfile));
                return;
            }
            else if (SubStrLastChars(argCODEfile, 3) == ".js") {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "js");
                FileDelete(Trim(argCODEfile));
                FileAppend(OUTCODE, Trim(argCODEfile));
                return;
            }
            else if (SubStrLastChars(argCODEfile, 3) == ".go") {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "go");
                FileDelete(Trim(argCODEfile));
                FileAppend(OUTCODE, Trim(argCODEfile));
                return;
            }
            else if (SubStrLastChars(argCODEfile, 4) == ".lua") {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "lua");
                FileDelete(Trim(argCODEfile));
                FileAppend(OUTCODE, Trim(argCODEfile));
                return;
            }
            else if (SubStrLastChars(argCODEfile, 3) == ".cs") {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "cs");
                FileDelete(Trim(argCODEfile));
                FileAppend(OUTCODE, Trim(argCODEfile));
                return;
            }
            else if (SubStrLastChars(argCODEfile, 5) == ".java") {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "java");
                FileDelete(Trim(argCODEfile));
                FileAppend(OUTCODE, Trim(argCODEfile));
                return;
            }
            else if (SubStrLastChars(argCODEfile, 3) == ".kt") {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "kt");
                FileDelete(Trim(argCODEfile));
                FileAppend(OUTCODE, Trim(argCODEfile));
                return;
            }
            else if (SubStrLastChars(argCODEfile, 3) == ".rb") {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "rb");
                FileDelete(Trim(argCODEfile));
                FileAppend(OUTCODE, Trim(argCODEfile));
                return;
            }
            else if (SubStrLastChars(argCODEfile, 4) == ".nim") {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "nim");
                FileDelete(Trim(argCODEfile));
                FileAppend(OUTCODE, Trim(argCODEfile));
                return;
            }
            else if (SubStrLastChars(argCODEfile, 4) == ".ahk") {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "ahk");
                FileDelete(Trim(argCODEfile));
                FileAppend(OUTCODE, Trim(argCODEfile));
                return;
            }
            else if (SubStrLastChars(argCODEfile, 6) == ".swift") {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "swift");
                FileDelete(Trim(argCODEfile));
                FileAppend(OUTCODE, Trim(argCODEfile));
                return;
            }
            else if (SubStrLastChars(argCODEfile, 5) == ".dart") {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "dart");
                FileDelete(Trim(argCODEfile));
                FileAppend(OUTCODE, Trim(argCODEfile));
                return;
            }
            else if (SubStrLastChars(argCODEfile, 3) == ".ts") {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "ts");
                FileDelete(Trim(argCODEfile));
                FileAppend(OUTCODE, Trim(argCODEfile));
                return;
            }
            else if (SubStrLastChars(argCODEfile, 7) == ".groovy") {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", "groovy");
                FileDelete(Trim(argCODEfile));
                FileAppend(OUTCODE, Trim(argCODEfile));
                return;
            }
            else if (SubStrLastChars(argCODEfile, StrLen("." + Trim(StrSplit(StrReplace(FileRead(argHTVMinstr), Chr(13), ""), "\n", 2)))) == "." + Trim(StrSplit(StrReplace(FileRead(argHTVMinstr), Chr(13), ""), "\n", 2))) {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "notHTVM", Trim(StrSplit(StrReplace(FileRead(argHTVMinstr), Chr(13), ""), "\n", 2)));
                FileDelete(Trim(argCODEfile));
                FileAppend(OUTCODE, Trim(argCODEfile));
                return;
            } else {
                print("INVALID LANG!!!");
                return;
            }
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
            //;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
        } else {
            if (argLangTo != "") {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "full", argLangTo);
            } else {
                OUTCODE = compiler(argCODE, Trim(FileRead(argHTVMinstr)), "full");
            }
        }
        print(StringTrimRight(argCODEfile, StrLen(langFileExtension)) + langToConvertTo);
        if (langToConvertTo == "js" && useJavaScriptInAfullHTMLfile == "on") {
            FileDelete(StringTrimRight(argCODEfile, StrLen(langFileExtension)) + "html");
            FileAppend(OUTCODE, StringTrimRight(argCODEfile, StrLen(langFileExtension)) + "html");
        } else {
            FileDelete(StringTrimRight(argCODEfile, StrLen(langFileExtension)) + langToConvertTo);
            FileAppend(OUTCODE, StringTrimRight(argCODEfile, StrLen(langFileExtension)) + langToConvertTo);
        }
    }
    if (HTVM_getLang_HTVM() == "js") {
        print("JS");
    }
}
int main(int argc, char* argv[]) {
    HTVMv2();
    return 0;
}