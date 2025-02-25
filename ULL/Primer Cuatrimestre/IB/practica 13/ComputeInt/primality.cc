    std::string input;
    std::getline(std::cin, input);

    std::istringstream stream(input);
    std::vector<int> numbers;
    int number;

    // Dividir la cadena en números separados por espacios
    while (stream >> number) {
        numbers.push_back(number);
    }


    for (int num : numbers) {
        if (EsPrimo(num) || num == 0 || num == 1) {
            std::cout << num << " is prime" << std::endl;
        } else {
            std::cout << num << " is not prime" << std::endl;
        }
    }

    return 0;
}
                                                              89,1        Final

