/*
Purpose:
Generate a Gaussian-distributed sample and save one value per line in
tutorial07_gaussian_data.txt. The file becomes the input for the next two tutorials.
*/

void tutorial07_generate_gaussian_data()
{
    const int numberOfEvents = 5000;
    const double trueMean = 5.0;
    const double trueSigma = 1.2;

    // TRandom3 is a modern ROOT random-number generator; the fixed seed is repeatable.
    TRandom3 random(2026);

    // ofstream creates a text file for writing and replaces an older file of the same name.
    std::ofstream output("tutorial07_gaussian_data.txt");
    if (!output) {
        std::cerr << "Could not create tutorial07_gaussian_data.txt" << std::endl;
        return;
    }

    output << std::setprecision(10);
    for (int i = 0; i < numberOfEvents; ++i) {
        output << random.Gaus(trueMean, trueSigma) << '\n';
    }

    output.close();
    std::cout << "Wrote " << numberOfEvents
              << " values to tutorial07_gaussian_data.txt" << std::endl;
    std::cout << "Generation settings: mean = " << trueMean
              << ", sigma = " << trueSigma << std::endl;
}

/*
Questions to try:
1. Regenerate with a different seed. Which properties change and which remain stable?
2. How many events are needed before the sample mean is usually close to 5.0?
3. Change sigma from 1.2 to 0.2. How should the later histogram change?
*/
