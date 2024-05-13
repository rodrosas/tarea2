#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <map>

class AnalizadorDeEstadisticas {
public:
    AnalizadorDeEstadisticas(const std::string& rutaArchivo) : rutaArchivo_(rutaArchivo) {
        LeerDatos();
    }

    void CalcularEstadisticas() {
        if (datos_.empty()) {
            std::cerr << "Error: No hay datos para analizar." << std::endl;
            return;
        }

        auto moda = CalcularModa();
        auto mediana = CalcularMediana();
        auto media = CalcularMedia();

        MostrarResultados(moda, mediana, media);
    }

private:
    std::string rutaArchivo_;
    std::vector<double> datos_;

    void LeerDatos() {
        std::ifstream archivo(rutaArchivo_);
        if (!archivo.is_open()) {
            std::cerr << "Error al abrir el archivo." << std::endl;
            return;
        }

        std::copy(std::istream_iterator<double>(archivo),
                  std::istream_iterator<double>(),
                  std::back_inserter(datos_));
        archivo.close();
    }

    double CalcularModa() const {
        std::map<double, int> frecuencias;
        for (double dato : datos_) {
            frecuencias[dato]++;
        }

        double moda = 0.0;
        int maxFrecuencia = 0;
        for (const auto& par : frecuencias) {
            if (par.second > maxFrecuencia) {
                maxFrecuencia = par.second;
                moda = par.first;
            }
        }

        return moda;
    }

    double CalcularMediana() const {
        std::vector<double> copiaDatos = datos_;
        std::sort(copiaDatos.begin(), copiaDatos.end());

        int n = copiaDatos.size();
        if (n % 2 == 0) {
            return (copiaDatos[n / 2 - 1] + copiaDatos[n / 2]) / 2.0;
        } else {
            return copiaDatos[n / 2];
        }
    }

    double CalcularMedia() const {
        double suma = 0.0;
        for (double dato : datos_) {
            suma += dato;
        }
        return suma / datos_.size();
    }

    void MostrarResultados(double moda, double mediana, double media) const {
        std::cout << "Resultados:" << std::endl;
        std::cout << "Moda: " << moda << std::endl;
        std::cout << "Mediana: " << mediana << std::endl;
        std::cout << "Media: " << media << std::endl;
    }
};

int main() {
    AnalizadorDeEstadisticas analizador("C:/Users/Multicomp/Desktop/tarea/datos.txt");
    analizador.CalcularEstadisticas();
    
    // Simulación de otras operaciones
    std::cout << "Otras operaciones realizadas..." << std::endl;
    
    return 0;
}
