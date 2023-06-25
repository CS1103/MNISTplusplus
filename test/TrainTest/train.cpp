#include "neural_network.h"
#include "mnist_loader.h"
#include "dataset.h"
#include "cmath"
#include <time.h>

void train(Dataset* dataset){

    //Create neural network
    size_t epochs = 100, batch_size = 150;
    neural_network nn;
    nn.add_layer(784,128);
    nn.add_layer(128,32);
    nn.add_layer(32,10);

    //Train algorithm
    cout << "Training..." << endl;
    int contador = 0;
    ;
    for(int i = 0; i < epochs; i++){
        cout << "Epoch: " << i << endl;
        auto batch = dataset->extract_training_batch(batch_size,12);

        double error_medio = 0;

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
                cout << "Numero Real: "<< real <<"  ||  ";
                cout << "O.H.E = "<< digit_image.get_label()<<'\n';
                cout << "Numero Predicho: " << max << endl;
                cout << std::string(20, '-')<< endl;
            }
            contador++;
        }
        for(auto& l: nn.get_layers()){
            l.gradient_descent(nn.get_learning_rate(), (int)batch_size);
        }
    }
    nn.serialize("../Models/trained_100_epch.txt");
}

void test(Dataset* dataset){

    auto testImages = dataset->get_test_data();

    neural_network nn;
    nn.deserialize("../Models/trained_100_epch.txt");

    double correct = 0;

    cout << "Testeo de la red neuronal" << endl;
    for(int i = 0; i<10000; i++){

        auto img = testImages[i].get_image();
        auto resp = nn.inference(img);


        int real = 0;
        for(int neuron = 0; neuron <10; neuron++ ){
            if(testImages[i].get_label()[neuron][0] == 1) {
                real = neuron;
                break;
            }
        }
        int max = 0;
        for(int neuron =0; neuron<10; neuron++){
            if(resp[neuron][0] > resp[max][0])
                max = neuron;
        }

        if (real == max)
            correct++;
        if (i%1000 == 0){
            cout << std::string(20, '-') << endl;
            cout << "Numero Real: " << real << "  ||  ";
            cout << "O.H.E = " << testImages[i].get_label() << '\n';
            cout << "Numero Predicho: " << max << endl;
        }
    }
    cout << "Porcentaje de acierto: " << (correct/10000.0)*100.0 << "%" << endl;
}

int main(){
    Dataset* dataset =  Dataset::GetInstance();
    train(dataset);
    test(dataset);
}