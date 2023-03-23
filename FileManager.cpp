#include "FileManager.h"

/////////////////////////////////////////////////////////////////////
// Definitions for methods for derived class Files

// Define function showContents_ for the Files class, taking a fs::path argument
void Files::showContents_(fs::path path)
{
    // Check if the path exists
    if (!fs::exists(path))
    {
        // Print an error message and return if the path doesn't exist
        std::cout << "Path does not exist.\n";
        return;
    }

    // Check if the path is a directory
    if (fs::is_directory(path))
    {
        // Print a message indicating that Folders class should be used instead to
        // show the contents
        std::cout << "Path is a directory. Use Folders class to show contents.\n";
        return;
    }

    // Print the path of the file whose contents are going to be displayed
    std::cout << "Contents of " << path << ":\n";

    // Open the file
    std::ifstream file(path);

    // Declare a string variable to store the lines of the file
    std::string line;

    // Read the file line by line and display the contents on the screen
    while (std::getline(file, line))
    {
        std::cout << line << '\n';
    }

    // Close the file
    file.close();
}

// Define function create_ for the Files class, taking a fs::path argument
void Files::create_(fs::path path)
{
    // Check if the file already exists
    if (fs::exists(path))
    {
        // Print an error message and return if the file already exists
        std::cout << "File already exists.\n";
        return;
    }

    // Create the file
    std::ofstream file(path);

    // Check if the file was successfully created
    if (file)
    {
        // Print a success message and close the file if the file was successfully
        // created
        std::cout << "File created successfully.\n";
        file.close();
    }
    else
    {
        // Print an error message if the file couldn't be created
        std::cout << "Failed to create file.\n";
    }
}

// Define function delete_ for the Files class, taking a fs::path argument
void Files::delete_(fs::path path)
{
    // Check if the file exists
    if (!fs::exists(path))
    {
        // Print an error message and return if the file doesn't exist
        std::cout << "File does not exist.\n";
        return;
    }

    // Check if the path is a directory
    if (fs::is_directory(path))
    {
        // Print a message indicating that Folders class should be used instead to
        // delete the directory
        std::cout << "Path is a directory. Use Folders class to delete.\n";
        return;
    }

    // Delete the file
    if (fs::remove(path))
    {
        // Print a success message if the file was successfully deleted
        std::cout << "File deleted successfully.\n";
    }
    else
    {
        // Print an error message if the file couldn't be deleted
        std::cout << "Failed to delete file.\n";
    }
}

void Files::rename_(fs::path oldPath, fs::path newPath)
{
    // check if the old path exists
    if (!fs::exists(oldPath))
    {
        // print an error message
        std::cout << "File does not exist.\n";
        // exit the function
        return;
    }

    // check if the old path is a directory
    if (fs::is_directory(oldPath))
    {
        // print an error message
        std::cout << "Path is a directory. Use Folders class to rename.\n";

        // exit the function
        return; // exit the function
    }
}

void Files::copy_(fs::path oldPath, fs::path newPath)
{
    // check if the source file exists
    if (!fs::exists(oldPath))
    {
        // print error message if it doesn't
        std::cout << "File does not exist.\n";

        // exit the function
        return;
    }

    // check if the source path is a directory
    if (fs::is_directory(oldPath))
    {
        // print error message if it is
        std::cout << "Path is a directory. Use Folders class to copy.\n";

        // exit the function
        return;
    }
    try
    {
        // copy the file to the destination path
        fs::copy_file(oldPath, newPath, fs::copy_options::overwrite_existing);

        // print success message
        std::cout << "File copied successfully.\n"; // print success message
    }
    // catch any exceptions that occur during the copy process
    catch (std::exception& e)
    {
        // print error message with exception details
        std::cout << "Failed to copy file. " << e.what() << "\n";
    }
}

void Files::move_(fs::path oldPath, fs::path newPath)
{
    if (!fs::exists(oldPath)) // check if the source file exists
    {
        std::cout << "File does not exist.\n"; // print error message if it doesn't
        return;                                // exit the function
    }
    if (fs::is_directory(oldPath)) // check if the source path is a directory
    {
        std::cout
            << "Path is a directory. Use Folders class to move.\n"; // print error
        // message if it
        // is
        return; // exit the function
    }
    try
    {
        fs::rename(oldPath, newPath); // move the file to the destination path
        std::cout << "File moved successfully.\n"; // print success message
    }
    catch (std::exception
           & e) // catch any exceptions that occur during the move process
    {
        std::cout << "Failed to move file. " << e.what()
            << "\n"; // print error message with exception details
    }
}

// This function calculates the size of a file or directory specified by path.
int Files::calculateSize_(fs::path path)
{
    // Check if path is a file
    if (fs::is_regular_file(path))
    {
        return fs::file_size(path); // Return file size in bytes
    }
    else                        // If path is a directory
    {
        int size = 0; // Initialize size to zero
        // Iterate over all entries in the directory
        for (const auto& entry : fs::directory_iterator(path))
        {
            if (fs::is_regular_file(entry.path())) // If entry is a file
            {
                size += fs::file_size(entry.path());     // Add file size to size
            }
            else if (fs::is_directory(entry.path())) // If entry is a directory
            {
                size += calculateSize_(entry.path()); // Recursively call the function
                // to get size of the directory
            }
        }
        return size; // Return total size in bytes
    }
}

/////////////////////////////////////////////////////////////////////
// Definitions for methods for derived class Folders

// This function shows the contents of a directory specified by path
void Folders::showContents_(fs::path path)
{
    // Check if path is a directory
    if (!fs::is_directory(path))
    {
        std::cerr << "Error: path is not a directory."
            << std::endl; // Print error message to stderr
        return;
    }

    // Iterate over all entries in the directory and print their paths
    for (const auto& entry : fs::directory_iterator(path))
    {
        std::cout << entry.path() << std::endl;
    }
}

// This function creates a new directory at the specified path.
void Folders::create_(fs::path path)
{
    if (fs::exists(path))
    {
        // Check if directory already exists
        std::cerr << "Error: path already exists." << std::endl;
        return;
    }
    // Create directory
    if (!fs::create_directory(path))
    {
        std::cerr << "Error: failed to create directory." << std::endl;
    }
}

// This function deletes a directory and its contents at the specified path.
void Folders::delete_(fs::path path)
{
    if (!fs::exists(path))
    {
        // Check if directory exists
        std::cerr << "Error: path does not exist." << std::endl;
        return;
    }
    if (!fs::is_directory(path))
    {
        // Check if path is a directory
        std::cerr << "Error: path is not a directory." << std::endl;
        return;
    }

    try
    {
        fs::remove_all(path);
    }
    // Catch and display any filesystem errors
    catch (const fs::filesystem_error& ex)
    {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
}

// This function renames a directory at the specified path.
void Folders::rename_(fs::path oldPath, fs::path newPath)
{
    // Check if the old path exists
    if (!fs::exists(oldPath))
    {
        std::cerr << "Error: path does not exist." << std::endl;
        return;
    }

    // Check if the old path is a directory
    if (!fs::is_directory(oldPath))
    {
        std::cerr << "Error: path is not a directory." << std::endl;
        return;
    }

    // Check if the new path already exists
    if (fs::exists(newPath))
    {
        std::cerr << "Error: path already exists." << std::endl;
        return;
    }

    // Rename the directory
    try
    {
        fs::rename(oldPath, newPath);
    }
    catch (const fs::filesystem_error& ex)
    {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
}

// This function copies a directory and its contents to the specified path.
void Folders::copy_(fs::path oldPath, fs::path newPath)
{
    // Check if the old path exists
    if (!fs::exists(oldPath))
    {
        std::cerr << "Error: path does not exist." << std::endl;
        return;
    }

    // Check if the old path is a directory
    if (!fs::is_directory(oldPath))
    {
        std::cerr << "Error: path is not a directory." << std::endl;
        return;
    }

    // Check if the new path already exists
    if (fs::exists(newPath))
    {
        std::cerr << "Error: path already exists." << std::endl;
        return;
    }

    // Copy the directory and its contents recursively
    try
    {
        fs::copy(oldPath, newPath, fs::copy_options::recursive);
    }
    catch (const fs::filesystem_error& ex)
    {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
}

void Folders::move_(fs::path oldPath, fs::path newPath)
{
    try
    {
        // Attempt to rename the old path to the new path
        fs::rename(oldPath, newPath);

        // If the rename was successful, output a success message
        std::cout << "Folder moved successfully!\n";
    }
    // If there was an error, catch it and output an error message
    catch (fs::filesystem_error const& e)
    {
        std::cerr << e.what() << '\n';
    }
}

int Folders::calculateSize_(fs::path path)
{
    // Initialize a variable to store the total size
    int total_size = 0;
    try
    {
        // Check if the path exists and is a directory
        if (fs::exists(path) && fs::is_directory(path))
        {
            // Iterate over all files in the directory and its subdirectories
            for (auto const& file : fs::recursive_directory_iterator(path))
            {
                // If the file is a regular file (not a directory or symlink), add its
                // size to the total
                if (fs::is_regular_file(file))
                {
                    total_size += fs::file_size(file);
                }
            }
        }
    }
    // If there was an error, catch it and output an error message
    catch (fs::filesystem_error const& e)
    {
        std::cerr << e.what() << '\n';
    }
    // Return the total size of all regular files in the directory and its
    // subdirectories
    return total_size;
}