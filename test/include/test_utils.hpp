#ifndef BRICK_TEST_UTILS_HPP_
#define BRICK_TEST_UTILS_HPP_

#include <algorithm>
#include <fstream>

namespace brick::test
{
  bool files_identical(const std::string& filename1, const std::string& filename2)
  {
    std::ifstream file1(filename1, std::ifstream::ate | std::ifstream::binary);
    std::ifstream file2(filename2, std::ifstream::ate | std::ifstream::binary);
    const std::ifstream::pos_type fileSize = file1.tellg();

    if (fileSize != file2.tellg()) {
      return false;
    }

    file1.seekg(0);
    file2.seekg(0);

    std::istreambuf_iterator<char> begin1(file1);
    std::istreambuf_iterator<char> begin2(file2);

    return std::equal(begin1, std::istreambuf_iterator<char>(), begin2);
  }
}

#endif
