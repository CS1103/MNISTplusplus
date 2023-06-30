#include "neural_network.h"
#include "utils.h"
#include "mnist_loader.h"
#include "dataset.h"
#include "cmath"

void train(){

    //Create neural network
    Dataset* dataset =  Dataset::GetInstance();

    size_t epochs = 250, batch_size = 320;
    neural_network nn;
    nn.add_layer(784,64);
    nn.add_layer(64,10);

    //Train algorithm
    cout << "Training..." << endl;
    int contador = 0;
    ;
    for(int i = 0; i < epochs; i++){
        cout << "Epoch: " << i << endl;
        auto batch = dataset->extract_training_batch(batch_size,12);

        for(auto& digit_image : batch){
            std::vector<std::pair<Matrix<double>, Matrix<double>>> y_pred = nn.forward(digit_image.get_image());
            Matrix<double> loss = nn.cost(digit_image.get_label(), y_pred.back().second);

            //Backward + update weights and biases
            nn.backward(digit_image.get_image(), digit_image.get_label());

            //Calcula el minimo cuadrado de la matriz de diferencia

            if(contador%150 == 0){
                auto img = digit_image.get_label();
                int max = 0;
                int real = 0;
                for(int neuron = 0; neuron <10; neuron++ ){
                    if(img(neuron,0) ==1 )
                        real = neuron;
                }
                for(int neuron =0; neuron<10; neuron++){
                    if(y_pred.back().second[neuron][0] > y_pred.back().second[max][0])
                        max = neuron;
                }

                cout << std::string(20, '-')<< endl;
                cout << "Ground truth: "<< real <<"  ||  ";
                cout << "O.H.E = "<< digit_image.get_label()<<'\n';
                cout << "Predicted: " << max << endl;
                cout << std::string(20, '-')<< endl;
            }
            contador++;
        }
        for(auto& l: nn.get_layers()){
            l.gradient_descent(nn.get_learning_rate(), (int)batch_size);
        }
    }
    nn.serialize("../models/trained_9178_epch.txt");
}

void test(){
    Dataset* dataset = Dataset::GetInstance();

    auto testImages = dataset->get_test_data();

    neural_network nn;
    nn.deserialize("../models/trained_9178_epch.txt");


    Matrix<double> confusion_matrix(10,10);
    double correct = 0;
    cout << "Validating neural network" << endl;
    for(int i = 0; i<dataset->test_data_size; i++) {

        auto img = testImages[i].get_image();
        auto resp = nn.inference(img);


        int ground_truth = argmax(testImages[i].get_label()).first;
        int predicted = argmax(resp).first;

        if (ground_truth == predicted)
            correct++;
        confusion_matrix[ground_truth][predicted]++;

    }
    vector<double> precision(10);
    for (int j = 0; j < 10; j++) {
        double sum = 0;
        for (int k = 0; k < 10; k++) {
            sum += confusion_matrix[k][j];
        }
        precision[j] = confusion_matrix[j][j] / (double) sum;
    }

    vector<double> recall(10);
    for (int j = 0; j < 10; j++) {
        double sum = 0;
        for (int k = 0; k < 10; k++) {
            sum += confusion_matrix[j][k];
        }
        recall[j] = confusion_matrix[j][j] / (double) sum;
    }
    cout << "\n------ Validation Results ------\n" << endl;

    cout << "\n| Class | Precision | Recall |\n";
    cout << "|------:|----------:|-------:|\n";
    for (int j = 0; j < 10; j++) {
        cout << "| " << setw(5) << j << " | " << setw(9) << setprecision(4) << precision[j] << " | " << setw(6) << setprecision(4) << recall[j] << " |\n";
    }
    cout << "\n";


    cout << "\n------ Overall Network Performance ------\n" << endl;
    cout << "Total Accuracy of the Network: " << setprecision(4) << (correct / dataset->test_data_size) * 100.0 << "%" << endl;

    cout << "\nConfusion Matrix: " << endl;

    cout << "|      ";
    for(int j = 0; j < 10; j++){
        cout << "| " << std::setw(3) << "C" << j << " ";
    }
    cout << "|\n";

    cout << "|------";
    for(int j = 0; j < 10; j++){
        cout << "|------";
    }
    cout << "|\n";

    for (int i = 0; i < confusion_matrix.get_rows(); ++i) {
        cout << "| " << std::setw(3) << "C" << i << " ";

        for (int j = 0; j < confusion_matrix.get_cols(); ++j) {
            cout << "| " << std::setw(4) << confusion_matrix(i, j) << " ";
        }
        cout << "|\n";
    }
    cout << "\n----------------------------------------\n" << endl;
}

int main(){
    //train();
    test();
}