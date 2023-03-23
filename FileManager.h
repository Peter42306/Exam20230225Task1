#pragma once
// Define a macro to silence the experimental filesystem deprecation warning
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

#include <iostream> // Include standard input/output stream library
#include <filesystem> // Include filesystem library
#include <string> // Include string library
#include <fstream> // Include file stream library

// Include experimental filesystem library
#include <experimental/filesystem> 

// Alias the experimental filesystem namespace to fs
namespace fs = std::experimental::filesystem;

/////////////////////////////////////////////////////////////////////

// Define an abstract class FileManager
class FileManager
{
public:
    // Declare pure virtual functions that must be implemented by derived classes

    // a pure virtual function declared in the abstract FileManager class
    // to be overridden by derived classes to provide implementation details
    // for showing the contents of a given path        
    virtual void showContents_(fs::path path) = 0;

    // pure virtual function declared in the abstract FileManager class
    // to be overridden by derived classes to provide implementation details 
    // for creating a new file or folder at a given path    
    virtual void create_(fs::path path) = 0;

    // a pure virtual function declared in the abstract FileManager class
    // to be overridden by derived classes to provide implementation details 
    // for deleting a file or folder at a given path    
    virtual void delete_(fs::path path) = 0;

    // pure virtual function declared in the abstract FileManager class
    // to be overridden by derived classes to provide implementation details 
    // for renaming a file or folder from the old path to the new path    
    virtual void rename_(fs::path oldPath, fs::path newPath) = 0;

    // pure virtual function declared in the abstract FileManager class
    // to be overridden by derived classes to provide implementation details 
    // for copying a file or folder from the old path to the new path    
    virtual void copy_(fs::path oldPath, fs::path newPath) = 0;

    // pure virtual function declared in the abstract FileManager class
    // to be overridden by derived classes to provide implementation details 
    // for moving a file or folder from the old path to the new path    
    virtual void move_(fs::path oldPath, fs::path newPath) = 0;

    // pure virtual function declared in the abstract class 
    // to be overridden by derived classes to provide implementation details 
    // for calculating the size of a file or folder at a given path    
    virtual int calculateSize_(fs::path path) = 0;
};

/////////////////////////////////////////////////////////////////////

// Define a derived class Files that inherits from FileManager
class Files : public FileManager
{
public:
    // Override the pure virtual functions from the base class with specific implementations for files

    void showContents_(fs::path path) override;
    void create_(fs::path path) override;
    void delete_(fs::path path) override;
    void rename_(fs::path oldPath, fs::path newPath) override;
    void copy_(fs::path oldPath, fs::path newPath) override;
    void move_(fs::path oldPath, fs::path newPath) override;
    int calculateSize_(fs::path path) override;
};

/////////////////////////////////////////////////////////////////////

// Define a derived class Folders that inherits from FileManager
class Folders : public FileManager
{
public:
    // Override the pure virtual functions from the base class with specific specific implementations for folders

    void showContents_(fs::path path) override;
    void create_(fs::path path) override;
    void delete_(fs::path path) override;
    void rename_(fs::path oldPath, fs::path newPath) override;
    void copy_(fs::path oldPath, fs::path newPath) override;
    void move_(fs::path oldPath, fs::path newPath) override;
    int calculateSize_(fs::path path) override;
};