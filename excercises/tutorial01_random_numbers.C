/*
Purpose:
Generate reproducible uniform random numbers with TRandom and print them in the
terminal. This is the first look at a ROOT class and a simple event loop.
*/

void tutorial01_random_numbers()
{
    // Declaration convention: ClassName variableName(constructor arguments).
    // Here TRandom is the class, random is our object, and 12345 is its seed.
    // A fixed seed makes the sequence repeatable, which is useful while testing code.
    TRandom random(12345);

    const int numberOfValues = 10;

    std::cout << "Uniform random numbers between 0 and 1" << std::endl;
    for (int i = 0; i < numberOfValues; ++i) {
        // Rndm() returns one value in the interval [0, 1).
        const double value = random.Rndm();
        std::cout << "value " << i + 1 << " = " << value << std::endl;
    }
}

/*
Questions to try:
1. What changes when the seed 12345 is replaced by 9876?
2. What happens when the seed is set to 0?
3. How would you transform Rndm() so the values lie between -5 and 5?
4. Increase numberOfValues to 1000. Is printing every simulated event still useful?
*/
