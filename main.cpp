// Define a macro to silence the experimental filesystem deprecation warning
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

// Include standard libraries

#include "FileManager.h" // Include header file
#include <filesystem>    // Include filesystem library
#include <fstream>       // Include file stream library
#include <iostream>      // Include standard input/output stream library
#include <string>        // Include string library

// Include experimental filesystem library
#include <experimental/filesystem>

// Alias the experimental filesystem namespace to fs
namespace fs = std::experimental::filesystem;

/////////////////////////////////////////////////////////////////////

int main()
{
	// Print a message to the console indicating that the main function is working
	std::cout << "This is the main() function is working\n";

	// Create an instance of the Files class
	Files files;

	// Define paths for a file, a new file, a directory, and a new directory
	fs::path filePath = "file.txt";
	fs::path newFilePath = "newfile.txt";
	fs::path dirPath = "directory";
	fs::path newDirPath = "new_directory";

	// Create a new file at the specified path
	files.create_(filePath);

	// Print the contents of the file to the console
	files.showContents_(filePath);

	// Rename the file at the original path to the new path
	files.rename_(filePath, newFilePath);

	// Delete the file at the new path
	files.delete_(newFilePath);

	// Create a new directory at the specified path
	fs::create_directory(dirPath);

	// Copy the contents of the original directory to the new directory
	files.copy_(dirPath, newDirPath);

	// Move the contents of the new directory back to the original directory
	files.move_(newDirPath, dirPath);

	// Calculate and print the total size of the original directory in bytes
	std::cout << "Total size: " << files.calculateSize_(dirPath) << " bytes\n";

	// Return 0 to indicate successful execution of the program
	return 0;
}