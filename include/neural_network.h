#ifndef MNISTPLUSPLUS_NEURAL_NETWORK_H
#define MNISTPLUSPLUS_NEURAL_NETWORK_H

#include <ranges>
#include <cmath>
#include <utility>
#include <vector>
#include <stack>
#include <fstream>
#include <sstream>
#include <initializer_list>

#include "neural_layer.h"
#include "constants.h"
#include "utils.h"
#include "digit_image.h"

class neural_network {
private:
    std::vector<neural_layer<double>> layers;
    double learning_rate = 0.4;

public:
    neural_network() = default;

    neural_network(std::initializer_list<neural_layer<double>> list) : layers(list) {}

    void add_layer(neural_layer<double>& layer) {
        layers.push_back(layer);
    }

    void add_layer(size_t input_size, size_t output_size) {
        layers.emplace_back(input_size, output_size);
    }

    Matrix<double> inference(const Matrix<double>& input) {
        std::pair<Matrix<double>,Matrix<double> > activation = { Matrix<double>(1,1),std::move(input.flatten())};
        for (auto& layer : layers)  activation = layer.forward(activation.second);
        return activation.second;
    }

    Matrix<double> cost ( const Matrix<double>& target, Matrix<double>& prediction){

        Matrix<double> log_pred(prediction.get_rows(), prediction.get_cols());
        for(int row =0; row < prediction.get_rows(); row++){
            for(int col = 0; col < prediction.get_cols(); col++){
                log_pred(row,col) = log(prediction(row,col));
            }
        }

        return -1.0 * (target ^ log_pred);
    }

    std::vector <std::pair<Matrix<double>,Matrix<double>>> forward(const Matrix<double>& input) {

        Matrix<double> activation = input.flatten();

        std::vector <std::pair<Matrix<double>,Matrix<double>>> out = {{ Matrix<double>(1,1),activation}};

        for (auto l=0; l<layers.size(); l++){
            if(l == layers.size()-1){
                out.push_back(layers[l].forward(activation, true));

            }else{
                out.push_back(layers[l].forward(activation));
                activation = out.back().second;
            }
        }

        return out;
    }

    Matrix<double> backward(const Matrix<double>& input,const Matrix<double>& label) {

        // Forward
        std::vector<std::pair<Matrix<double>,Matrix<double>>> out = forward(input);

        // Backward + Gradient descent

        std::vector<Matrix<double>> deltas;
        Matrix<double> current_loss  = cost(label, out.back().second);

        auto w_ = layers[layers.size()-1].get_w();

        for(int l = (int)layers.size()-1; l >= 0; l--){

            auto &a_ = out[l+1].second;

            if(l == layers.size()-1){
                Matrix<double> last_da = (a_ - label);
                deltas.insert( deltas.begin(), layers[l].backward_softmax(last_da , out[l].second));
            }else{
                deltas.insert(deltas.begin(), layers[l].backward_relu(deltas[0], out[l].second, out[l+1].first));
            }
        }

        return current_loss;
    }

    std::vector<neural_layer<double>>& get_layers() {
        return layers;
    }

    neural_layer<double>& operator[](size_t pos) {
        return layers[pos];
    }

    size_t size() {
        return layers.size();
    }

    double get_learning_rate() const {
        return learning_rate;
    }

    static std::string trim(std::string &str){
        int first_char = 0, last_char=(int)str.length()-1;

        for (int i = 0; i < str.length();  i++){
            if(str[i] != ' ' && str[i] != '\n'){
                first_char = i;
                break;
            }
        }

        for (int i = (int)str.length()-1; i>0; i--){
            if(str[i] != ' ' && str[i] != '\n'){
                last_char = i;
                break;
            }
        }

        str = str.substr(first_char, last_char-first_char+1);
        return str;
    }

    void serialize(const string& filename){
        ofstream file(filename);
        if(!file.is_open()){
            throw runtime_error("Error opening file");
        }
        file << SERIALIZE_MAGIC_NUMBER << "\n";
        file << "n_layers : " << layers.size() << ",\n";
        file << "layers : {\n";

        for(int i = 0; i < layers.size(); i++){
            file << "   layer_" << i << " : {\n";
            file << "       input_size: " << layers[i].get_input_size() << ",\n";
            file << "       output_size: " << layers[i].get_output_size() << ",\n";
            file << "        w: [" << layers[i].get_w() << "],\n";

            file << "        b: [" << layers[i].get_b() << "],\n";
            file << "    },\n";
        }
        file << "},\n";
        file.close();
    }

    void deserialize(const string& filename){
        ifstream file(filename);
        if(!file.is_open()){
            throw runtime_error("Error opening file");
        }
        string line;
        getline(file, line);

        if(line != SERIALIZE_MAGIC_NUMBER){
            throw runtime_error("Invalid file");
        }


        int n_layers;
        int input_size=0, output_size=0;
        vector<Matrix<double>> layer;
        vector<int> sizes;

        while(getline(file, line)){

            string token;
            istringstream ss(line);
            getline(ss, token, ':');

            if(trim(token) == "n_layers"){
                getline(ss, token, ',');

                n_layers = stoi(trim(token));
            }
            else if(trim(token) == "layers"){
                int current_layer = 0;
                stack<string> seps;

                getline(ss, token);
                seps.push(trim(token));

                getline(file, line);

                seps.emplace(trim(line)[line.length()-1] == '{'? "{":"[");


                while(getline(file,line) && !seps.empty()){

                    if(  trim(line)[0] == '}'||
                         trim(line)[0] == ']'){
                        seps.pop();
                        getline(file, line);
                    }
                    else if( trim(line)[line.length()-1] == '{'||
                             trim(line)[line.length()-1] == '['){
                        string sep = trim(line)[line.length()-1] == '{' ? "{":"[";
                        seps.push(sep);
                        getline(file, line);
                    }
                    ss.clear();
                    ss.str(trim(line));
                    getline(ss, token, ':');

                    if(trim(token) == "input_size"){
                        getline(ss, token,',');
                        input_size = stoi(token);
                        sizes.push_back(input_size);
                        getline(ss,token);


                        if(seps.top() == "{" && trim(token) == "}" || seps.top() == "[" && trim(token) == "]") seps.pop();
                    }
                    else if(trim(token) == "output_size"){
                        getline(ss, token,',');
                        output_size = stoi(token);
                        sizes.push_back(output_size);


                        if(seps.top() == "{" && trim(token) == "}" || seps.top() == "[" && trim(token) == "]") seps.pop();
                    }
                    else if(trim(token) =="w"){
                        layer.emplace_back(input_size, output_size);
                        seps.emplace("[");
                        getline(ss,token,'[');

                        for(int rows =0; rows < input_size; rows++){
                            for(int cols=0; cols < output_size; cols++){
                                getline(ss,token,' ');
                                layer[current_layer](rows,cols) = stod(token);
                            }
                        }
                        getline(ss,token,',');
                        if(seps.top() == "{" && trim(token) == "}" || seps.top() == "[" && trim(token) == "]") seps.pop();

                    }else if(trim(token) =="b"){
                        layer.emplace_back(output_size,1);
                        seps.emplace("[");
                        getline(ss,token,'[');

                        for(int rows =0; rows < output_size; rows++){
                            getline(ss,token,' ');
                            layer[current_layer+1](rows,0) = stod(token);
                        }
                        current_layer += 2;
                        //getline(ss,token,',');
                        if( seps.top() == "{" && trim(token) == "}" || seps.top() == "[" && trim(token) == "]") seps.pop();

                    }
                }
            }
        }
        for(int i = 0; i < layer.size(); i+=2)
            layers.emplace_back(sizes[i], sizes[i+1], layer[i], layer[i+1]);
    }

};



#endif //MNISTPLUSPLUS_NEURAL_NETWORK_H
