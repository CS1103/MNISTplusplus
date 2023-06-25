#include "neural_network.h"
#include "mnist_loader.h"
#include "dataset.h"
#include "cmath"
#include <time.h>

void train(){

    Dataset* dataset =  Dataset::GetInstance();

    size_t epochs = 12, batch_size = 30;
    neural_network nn;
    nn.add_layer(784,7);
    nn.add_layer(7,10);

    //nn.add_layer(7,10);

    //Train algorithm
    cout << "Training..." << endl;
    int contador = 0;
    for(int i = 0; i < epochs; i++){
        cout << "Epoch: " << i << endl;
        auto batch = dataset->extract_training_batch(batch_size,12);

        double error_medio = 0;

        for(auto& digit_image : batch){

            std::vector<std::pair<Matrix<double>, Matrix<double>>> y_pred = nn.forward(digit_image.get_image());
            Matrix<double> loss = nn.cost(digit_image.get_label(), y_pred.back().second);

            //Backward + update weights and biases
            nn.backward(digit_image.get_image(), digit_image.get_label());

            for(auto& l: nn.get_layers()){
                l.gradient_descent(nn.get_learning_rate(), (int)batch_size);
            }

            //Calcula el minimo cuadrado de la matriz de diferencia
            double error =0;
            for(int neuron = 0; neuron <10; neuron++ ){
                error += pow(loss[neuron][0],2);
            }
            error_medio += error;
            if(contador%14 == 0){
                int max = 0;
                int real = 0;
                for(int neuron = 0; neuron <10; neuron++ ){
                    if(digit_image.get_label()[neuron][0] > digit_image.get_label()[max][0])
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
                //cout << y_pred.back().second << endl;
                cout << std::string(20, '-')<< endl;

            }

            contador++;
        }
        cout << "Error medio: " << error_medio/(int)batch_size << endl;
    }


    nn.serialize("nn.txt");
}

void test(){
    neural_network nn;
    nn.deserialize("nn.txt");

    MNISTReader loader;
    loader.load_test_dataset();

    srand (time(0));

    int batch_size = 32;

    cout << "Testeo de la red neuronal" << endl;
    for(int i = 0; i<100; i++){
        int n = rand() % 100;
        auto trainImages = loader.get_test_data();
        auto img = trainImages[n].get_image();
        auto resp = nn.inference(img);

        int max = 0;
        int real = 0;
        for(int neuron = 0; neuron <10; neuron++ ){
            if(loader.get_test_data()[n].get_label()[neuron][0] > loader.get_test_data()[n].get_label()[max][0])
                real = neuron;
        }
        for(int neuron =0; neuron<10; neuron++){
            if(resp[neuron][0] > resp[max][0])
                max = neuron;
        }

        if(i%10 == 0){
            cout << std::string(20, '-') << endl;
            cout << "Numero Real: " << real << "  ||  ";
            cout << "O.H.E = " << loader.get_test_data()[n].get_label() << '\n';
            cout << "Numero Predicho: " << max << endl;
        }
    }

}
int main(){
    train();
    test();
}