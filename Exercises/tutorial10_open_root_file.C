/*
Purpose:
Open the ROOT file made in tutorial 9, retrieve the stored histogram and fit,
detach copies from the file, and draw them on a new canvas.
*/

void tutorial10_open_root_file()
{
    // READ opens an existing ROOT file without changing it.
    TFile input("tutorial09_gaussian_fit.root", "READ");
    if (input.IsZombie()) {
        std::cerr << "ROOT file not found. Run tutorial 9 first." << std::endl;
        return;
    }

    // Type *name declares a pointer: it stores the address of an object rather
    // than containing the object itself. nullptr means it points to nothing yet.
    TH1D *storedHistogram = nullptr;
    TF1 *storedFit = nullptr;

    // GetObject finds each named object, checks its class, and sets the pointer
    // to the object's address. The file owns these retrieved objects.
    input.GetObject("gaussian_histogram", storedHistogram);
    input.GetObject("gaussian_fit", storedFit);

    if (storedHistogram == nullptr || storedFit == nullptr) {
        std::cerr << "The expected histogram or fit is missing." << std::endl;
        input.ls();
        return;
    }

    // Pointer member functions use -> instead of the dot used by ordinary objects.
    // Clone returns an independent object; the cast records its expected pointer type.
    // We clone before closing the file because the file owns the stored versions.
    TH1D *histogram = static_cast<TH1D *>(storedHistogram->Clone("display_histogram"));
    TF1 *fit = static_cast<TF1 *>(storedFit->Clone("display_fit"));
    histogram->SetDirectory(nullptr);
    input.Close();

    TCanvas canvas("canvas", "Objects reopened from file", 800, 600);
    histogram->SetTitle("Reopened Gaussian fit;Measured value;Entries");
    histogram->Draw("E");
    fit->SetLineColor(kRed + 1);
    fit->Draw("same");
    canvas.SaveAs("tutorial10_reopened_gaussian_fit.png");

    std::cout << "Reopened fit mean  = " << fit->GetParameter(1) << std::endl;
    std::cout << "Reopened fit sigma = " << fit->GetParameter(2) << std::endl;
}

/*
Questions to try:
1. What happens if the object name is misspelled in GetObject()?
2. Why are the objects cloned before the input file is closed?
*/
