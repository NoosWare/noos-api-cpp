#include <noos/noos>
#include <iostream>
#include <chrono>

// TODO: REMOVE THIS EXAMPLE

/// \brief function to read a json file and it is converted 
//  into a string param
std::string read_json_file(const std::string file)
{
    if (file.empty()){
        throw std::runtime_error("empty file param");
    }
    std::ifstream t(file);
    if (t.good()) {
	std::stringstream buffer;
	buffer << t.rdbuf();
	t.close();
	return buffer.str();
    }
    else {
        throw std::runtime_error("failed to open ifsteam");
    }
}

int main()
{
    return 0;
}
