#include <iostream>
#include <random>
#include <sstream>
#include <iomanip>
#include <string>

std::string generateRandomWord(int length) {
    std::string output = "";
    int ASCII_MIN = 33;
    int ASCII_MAX = 123;
    std::random_device device;
    std::mt19937 rng(device());
    std::uniform_int_distribution<std::mt19937::result_type> dist(ASCII_MIN, ASCII_MAX);

    for (int i = 0; i<length; i++) {
         output += char(dist(rng));
    }
    return output;
}

std::stringstream generateStream() {
    bool one = true;
    int length[4] = {10, 100, 500, 1000};
    std::stringstream output;
    for(int i = 0; i < 4; i++){
        for (int j = 0; j < 25000; j++) {
            std::string first = generateRandomWord(length[i]);
            std::string second = generateRandomWord(length[i]);
            while (first == second) {
                std::string first = generateRandomWord(length[i]);
                std::string second = generateRandomWord(length[i]); 
            }
            if (one) {
                output << first << " " << second;
                one = false;
            } else {
                output << std::endl << first << " " << second;
            }
        }
    }
    return output;
}

std::string int_to_hex( unsigned int i )
{
  std::stringstream stream;
  stream << std::setfill ('0') << std::setw(sizeof(unsigned int)*2) 
         << std::hex << i;
  return stream.str();
}

unsigned int countSetBits(unsigned int n) {
    unsigned int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

int leftRotate(int n, unsigned int d) {
    return (n << d)|(n >> (32 - d));
}

std::string hash(std::string input) {
    std::string output;

    unsigned int hexes[8] = {3189621198, 721040558, 2888932716, 1761483275, 152458759, 2779224377, 4151057064, 1000842129};

    int length = input.length();

    int num = 1153;
    int sum = num;

    for (int i = 0; i < length; i++){
        // sum *= (int(input[i]) | int(input[i]) ^ sum);
        sum = num|(int(input[i])/sum);
        num = leftRotate(num, 5) + int(input[i]) - num;
    }

    // for (int i = 0; i < 4; i++) {
    //     hexes[i] = hexes[i]^hexes[7-i];
    //     hexes[7-i] = hexes[7-i]^(~hexes[i]);
    // }
    std::string numberasstring = std::to_string(num*num);
    int numLen = numberasstring.length();
    
    for (int i = 0; i< 8; i++) {
        hexes[i] = (hexes[int(numberasstring[(i*2)%numLen])] | hexes[int(numberasstring[(i*2+1)%numLen])]);
    }
    for (int i = 0; i < 8; i++) {
        output += int_to_hex(hexes[i]^(num*sum));
    }
    return output;
}

void testCollisions(std::stringstream& stream) {
    int collisions = 0;
    while (!stream.eof()) {
        std::string first, second;
        stream >> first >> second;
        if (hash(first) == hash(second)) {
            collisions++;
        }
    }
    std::cout << "Colisions: " << collisions << std::endl;
}

int main() {
    std::cout << "Hash a: " << hash("ab") << std::endl;
    std::cout << "Hash b: " << hash("ba") << std::endl;
    std::cout << "Hash long text: " << hash("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras lobortis sapien nulla, nec suscipit nibh sollicitudin eu. Donec sollicitudin ligula vel nunc ultricies, in condimentum quam mollis. Phasellus consectetur mauris orci, id feugiat velit condimentum at. Donec tincidunt neque vitae commodo dapibus. Proin congue aliquet arcu, eget egestas magna ultricies vitae. Suspendisse ac interdum eros, vehicula consequat dui. Aliquam et tellus a lectus maximus viverra. Sed cursus sollicitudin nulla, et ultrices libero tempus eget. Integer ultricies ut metus non consequat. Integer viverra placerat lectus, eget porta purus ultrices vitae. Quisque ut metus urna. Etiam sagittis dignissim tempus. Fusce accumsan ipsum quis purus egestas, nec pharetra neque sodales. Aliquam et lorem lectus.Duis ornare sapien sed massa condimentum efficitur. Nunc sollicitudin vulputate ante, non sollicitudin turpis viverra a. Ut tempus, urna vel imperdiet vehicula, lorem nisl viverra nisl, sed auctor massa metus vel eros. Integer scelerisque ante sed sem eleifend, quis imperdiet turpis iaculis. Sed volutpat risus venenatis ex tempor, eu malesuada lorem auctor. Suspendisse potenti. Mauris sit amet orci in nibh finibus semper. Donec eu nisi ac ante tempor lacinia. Proin luctus accumsan nulla, molestie ultricies lorem ornare quis. Vestibulum ac lorem et velit venenatis placerat vitae nec lorem. Nunc viverra bibendum elit sit amet imperdiet. Nulla fermentum orci quis velit dictum sagittis. Pellentesque ac bibendum orci.Donec sit amet lobortis nisi. Curabitur congue enim in tincidunt lobortis. Vivamus condimentum, leo sed ornare condimentum, justo ligula pretium arcu, fringilla consequat metus purus ut lorem. Praesent ultrices, turpis sit amet tincidunt elementum, lorem quam pellentesque tortor, sodales egestas eros libero sed orci. Fusce ullamcorper ligula sed lectus malesuada, vel auctor risus vestibulum. Vestibulum eget tincidunt quam, nec eleifend mi. Nulla eu velit in risus consequat ullamcorper gravida placerat leo. Aenean id porta arcu, vel imperdiet nibh.Nulla finibus, sem a rutrum maximus, velit mi eleifend tellus, eu tincidunt tortor nisi in elit. Praesent nunc felis, dictum eu ex ut, vestibulum dictum tortor. Vestibulum malesuada fringilla eros, eu dictum odio scelerisque et. Etiam condimentum eleifend arcu at faucibus. Suspendisse potenti. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Integer ut finibus ex. Suspendisse sed iaculis libero, sit amet consectetur mi. Donec ac elit dolor. Cras sit amet mauris blandit, feugiat ante a, tincidunt elit. Integer eu cursus sem. Mauris vitae turpis eget massa vestibulum ornare ac sed diam. Duis sit amet mauris lectus. Etiam vel molestie enim, ut pulvinar eros. Nulla facilisi. Nulla ornare egestas euismod.Sed sit amet lectus sit amet enim lobortis finibus id sed mauris. Praesent rhoncus volutpat mi eget tempor. Nunc semper urna vel feugiat porttitor. Nulla at elit turpis. Quisque eget nisi vulputate, gravida quam rutrum, pharetra metus. Cras tincidunt mattis tortor vitae lobortis. Vivamus a hendrerit nibh, eu faucibus augue. Maecenas finibus auctor est vel dapibus. Fusce non tortor ante. ") << std::endl;
    std::cout << "Hash long text: " << hash("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras lobortis sapien nulla, nec suscipit nibh sollicitudin eu. Donec sollicitudin ligula vel nunc ultricies, in condimentum quam mollis. Phasellus consectetur mauris orci, id feugiat velit condimentum at. Donec tincidunt neque vitae commodo dapibus. Proin congue aliquet arcu, eget egestas magna ultricies vitae. Suspendisse ac interdum eros, vehicula consequat dui. Aliquam et tellus a lectus maximus viverra. Sed cursus sollicitudin nulla, et ultrices libero tempus eget. Integer ultricies ut metus non consequat. Integer viverra placerat lectus, eget porta purus ultrices vitae. Quisque ut metus urna. Etiam sagittis dignissim tempus. Fusce accumsan ipsum quis purus egestas, nec pharetra neque sodales. Aliquam et lorem lectus.Duis ornare sapien sed massa condimentum efficitur. Nunc sollicitudin vulputate ante, non sollicitudin turpis viverra a. Ut tempus, urna vel imperdiet vehicula, lorem nisl viverra nisl, sed auctor massa metus vel eros. Integer scelerisque ante sed sem eleifend, quis imperdiet turpis iaculis. Sed volutpat risus venenatis ex tempor, eu malesuada lorem auctor. Suspendisse potenti. Mauris sit amet orci in nibh finibus semper. Donec eu nisi ac ante tempor lacinia. Proin luctus accumsan nulla, molestie ultricies lorem ornare quis. Vestibulum ac lorem et velit venenatis placerat vitae nec lorem. Nunc viverra bibendum elit sit amet imperdiet. Nulla fermentum orci quis velit dictum sagittis. Pellentesque ac bibendum orci.Donec sit amet lobortis nisi. Curabitur congue enim in tincidunt lobortis. Vivamus condimentum, leo sed ornare condimentum, justo ligula pretium arcu, fringilla consequat metus purus ut lorem. Praesent ultrices, turpis sit amet tincidunt elementum, lorem quam pellentesque tortor, sodales egestas eros libero sed orci. Fusce ullamcorper ligula sed lectus malesuada, vel auctor risus vestibulum. Vestibulum eget tincidunt quam, nec eleifend mi. Nulla eu velit in risus consequat ullamcorper gravida placerat leo. Aenean id porta arcu, vel imperdiet nibh.Nulla finibus, sem a rutrum maximus, velit mi eleifend tellus, eu tincidunt tortor nisi in elit. Praesent nunc felis, dictum eu ex ut, vestibulum dictum tortor. Vestibulum malesuada fringilla eros, eu dictum odio scelerisque et. Etiam condimentum eleifend arcu at faucibus. Suspendisse potenti. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Integer ut finibus ex. Suspendisse sed iaculis libero, sit amet consectetur mi. Donec ac elit dolor. Cras sit amet mauris blandit, feugiat ante a, tincidunt elit. Integer eu cursus sem. Mauris vitae turpis eget massa vestibulum ornare ac sed diam. Duis sit amet mauris lectus. Etiam vel molestie enim, ut pulvinar eros. Nulla facilisi. Nulla ornare egestas euismod.Sed sit amet lectus sit amet enim lobortis finibus id sed mauris. Praesent rhoncus volutpat mi eget tempor. Nunc semper urna vel feugiat porttitor. Nulla at elit turpis. Quisque eget nisi vulputate, gravida quam rutrum, pharetra metus. Cras tincidunt mattis tortor vitae lobortis. Vivamus a hendrerit nibh, eu faucibus augue. Maecenas finibus auctor est vel dapibus. Fusce non tortor anta. ") << std::endl;
    std::stringstream stream = generateStream();
    testCollisions(stream);
    // std::cout << hash("hello world");
}

