#include "source_file.h"

SourceFile::SourceFile(std::string command) {
  // std::ofstream myOutStream(myCurrentLogName.c_str(), std::ios::app);
  this->lineNumber = 0;
  this->position = 0;
  this->command = command;
  this->currentLine = command;
};

int SourceFile::nextChar() {
  if(this->position > this->currentLine.size()) {
    return EOF;
    // }
    // this->lineNumber++;
    // this->position = 0;
  }
  return this->currentLine[this->position++];
};

int SourceFile::previewChar() {
  return this->currentLine[this->position];
};

void SourceFile::restoreChar() {
  if(this->position > 0)
    this->position--;;
};
