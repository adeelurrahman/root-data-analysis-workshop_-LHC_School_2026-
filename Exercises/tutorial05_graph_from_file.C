/*
Purpose:
Read x-y measurements from tutorial05_data.txt and plot them with TGraph. Unlike a
histogram, a graph keeps the coordinates of each measured point.
*/

void tutorial05_graph_from_file()
{
    std::ifstream input("tutorial05_data.txt");
    if (!input) {
        std::cerr << "Could not open tutorial05_data.txt" << std::endl;
        return;
    }

    // TGraph stores pairs of x and y coordinates.
    TGraph graph;

    double time = 0.0;
    double temperature = 0.0;
    int point = 0;

    while (input >> time >> temperature) {
        // SetPoint uses a zero-based point index followed by x and y.
        graph.SetPoint(point, time, temperature);
        ++point;
    }

    std::cout << "Read " << graph.GetN() << " points" << std::endl;

    TCanvas canvas("canvas", "Graph from file", 800, 600);
    graph.SetTitle("Cooling measurement;Time [min];Temperature [C]");
    graph.SetMarkerStyle(20);
    graph.SetMarkerSize(1.1);
    graph.SetLineColor(kBlue + 1);
    graph.Draw("APL");
    canvas.SetGrid();
    canvas.SaveAs("tutorial05_graph_from_file.png");
}

/*
Questions to try:
1. What changes when Draw("APL") becomes Draw("AP")?
2. Add a repeated x value to tutorial05_data.txt. Can TGraph display both measurements?
*/
