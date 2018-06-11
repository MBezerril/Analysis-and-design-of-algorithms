// APA-ColoracaoDeGrafos.cpp : define o ponto de entrada para o aplicativo do console.
//

#include "stdafx.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "vertice.h"

vertice *vertices;
int loopzaco = 0;
int quantidade;

bool inicializar() {
	std::ifstream arquivo("entrada.txt", std::ifstream::in);
	if (!arquivo.is_open())
		return false;
	std::string linhaLida, pedaco;
	std::stringstream linhaProcessar;
	std::getline(arquivo, linhaLida);
	linhaProcessar << linhaLida;
	linhaProcessar >> pedaco;
	if (pedaco != "p")
		return false;
	linhaProcessar >> pedaco;
	if (pedaco != "edge")
		return false;
	linhaProcessar >> pedaco;
	quantidade = std::stoi(pedaco);
	vertices = new vertice[quantidade];
	linhaProcessar >> pedaco;
	loopzaco = std::stoi(pedaco);

	for (int i = 0; i < loopzaco; i++) {
		int primeiro, segundo;
		std::getline(arquivo, linhaLida);
		linhaProcessar.clear();
		linhaProcessar.str(linhaLida);
		linhaProcessar >> pedaco; // tirar o 'e'
		linhaProcessar >> pedaco; // pega o primeiro
		primeiro = std::stoi(pedaco);
		linhaProcessar >> pedaco; // pega o segundo
		segundo = std::stoi(pedaco);
		//std::cout << primeiro << " : " << segundo << std::endl;
		primeiro--;
		segundo--;
		vertices[primeiro].InserirAdjacente(segundo);
		vertices[segundo].InserirAdjacente(primeiro);
	}
	return true;
}


int main() {

	if (!inicializar())
		return -1;
	std::vector<int> trancados;
	bool continua = 1;
	int cor = 1;
	while (continua) {
		continua = 0;
		for (int i = 0; i < quantidade; i++) {
			if (vertices[i].getCor() == 0 && vertices[i].getStatus() == 0) {
				// Adiciona u a classe i 
				vertices[i].setCor(cor);
				for (int j = 0; j < vertices[i].getQuantidadeAdjacentes(); j++) {
					if (vertices[vertices[i].getAdjacente(j)].getStatus() == 0 && vertices[vertices[i].getAdjacente(j)].getCor() == 0) {
						vertices[vertices[i].getAdjacente(j)].setStatus(1);
						trancados.push_back(vertices[i].getAdjacente(j));
						continua = 1;
					}

				}
			}
		}
		cor++;
		for (auto qqr : trancados) {
			vertices[qqr].setStatus(0);
		}
		trancados.clear();
	}
	for (int i = 0; i < quantidade;i++) {
		std::cout << "vertice:" << i << "-------------cor:" << vertices[i].getCor() 
			<<"----------------quantidade de Ligacoes:"<< vertices[i].getQuantidadeAdjacentes() << std::endl;
	}
	system("pause");
	return 0;
}

