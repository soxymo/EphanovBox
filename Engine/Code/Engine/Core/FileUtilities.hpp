/////////////////////////////////////////////////////////////////////////////////////////////////
// FileUtilities.hpp
//
// Basic file i/o utility functions.
//
#pragma once
#include <string>
#include <vector>


//-----------------------------------------------------------------------------------------------
bool LoadBinaryFileToBuffer( const std::string& filePath, std::vector< unsigned char >& out_buffer );
bool SaveBinaryFileFromBuffer( const std::string& filePath, const std::vector< unsigned char >& buffer );
