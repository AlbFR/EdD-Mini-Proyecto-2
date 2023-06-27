#include <random>
#include <iostream>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iomanip>

#include "src/QuadTree.h"

bool validate(int argc, char *argv[]);

int main(int argc, char *argv[]) {
	// srand(time(NULL));
	/*
	if (!validate(argc, argv)) {
		exit(1);
	}
	*/

	// Amount of data
	//const long long n = atoll(argv[1]);
	const long long n = 10000;
	// Defines weather or not will be displayed the text for human reading

	std::ofstream file;

	file.open("data.txt");

	// Testing constants
	const long long max_rand = 1e3; // exclusive
	long double tests = 1e6;
	const long double at_tests_factor = 1e1;
	const long long interval = 150;

	// HERE YOU DECLARE YOUR STUFF
	Node *root = NULL;

	
	std::cout << "Given n = " << n << std::endl	;

	long long val = rand();


	// insertNode method Testing
	for (long long i=0;i<n;i+=interval) {

		auto start_time = std::chrono::high_resolution_clock::now();
		for (long long j=i;j<i+interval;++j) {
			root = insertNode(root, j);
			for (long long k = 1; k < tests; ++k)
				insertNode(root, j);
		}
		auto end_time = std::chrono::high_resolution_clock::now();
		auto duration_time = (long double)std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
		
		/*
		while (size(root) < i)
			root = insertNode(root, rand()%max_rand);
		
		auto start_time = std::chrono::high_resolution_clock::now();
		for (long long j=i;j<i+interval;++j) {
			val += 1000000007;
			val %= max_rand;
			root = insertNode(root, val);
			for (long long k = 1; k < tests; ++k)
				insertNode(root, val);
		}
		auto end_time = std::chrono::high_resolution_clock::now();
		auto duration_time = (long double)std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
		*/


		std::cout << "For n=" << i << ", it takes " << std::fixed << std::setprecision(18) << duration_time/interval << " microseconds to insert a Node" << std::endl;
		file << std::fixed << std::setprecision(18) << duration_time / (interval*tests) << std::endl;
		
	}


	std::cout << "insert ha sido testeao :D" << std::endl;
	// the root is reset
	root = NULL;
	tests *= at_tests_factor;
	
	// at method Testing
	for (long long i=0;i<n;i+=interval) {

		for(long long j = i; j < i+interval; ++j) {
			root = insertNode(root, j);
		}
		
		auto start_time = std::chrono::high_resolution_clock::now();
		for (long long j=i;j<i+interval; ++j) {
			for (long long k = 0;k < tests; ++k)
				at(root, j);
		}
		auto end_time = std::chrono::high_resolution_clock::now();
		auto duration_time = (long double)std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
		
		std::cout << "For n=" << i << ", it takes " << std::setprecision(18) << duration_time/(interval*tests) << " microseconds to find a key" << std::endl;
		std::cout << duration_time << std::endl;
		file << std::fixed << std::setprecision(18) << duration_time / (interval*tests) << std::endl;
	}
	/*
	for (long long i=0;i<n;i+=interval) {
		auto start_time = std::chrono::high_resolution_clock::now();
		for (long long j=i;j<i+interval;++j) {
			val += 1000000007;
			val %= max_rand;
			for (long long k = 0;k < tests; ++k)
				at(root, val);
		}
		auto end_time = std::chrono::high_resolution_clock::now();
		auto duration_time = (long double)std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();

		while (size(root) < i+interval)
			root = insertNode(root, rand()%max_rand);

		if (display_text) {
			std::cout << "For n=" << i << ", it takes " << std::setprecision(18) << duration_time/(interval*tests) << " microseconds to find a key" << std::endl;
			std::cout << duration_time << std::endl;
		}
		else {
			file << std::fixed << std::setprecision(18) << duration_time / (interval*tests) << std::endl;
		}
	}
	*/
	
	std::cout << "Initial size before testing deleteNode method: " << size(root) << std::endl;
	tests /= at_tests_factor;
	
	
	for (long long i=0;i<n;i+=interval) {
		std::cout << i << std::endl;
		auto start_time = std::chrono::high_resolution_clock::now();
		for (long long j=i;j<i+interval;++j) {
			root = deleteNode(root, n-j-1);
			for (long long k = 0;k < tests; ++k)
				deleteNode(root, n-j-1);
		}
		auto end_time = std::chrono::high_resolution_clock::now();
		auto duration_time = (long double)std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();

/*
		auto start_time = std::chrono::high_resolution_clock::now();
		for (long long j=i;j<i+interval;++j) {
			val += 1000000007;
			val %= max_rand;
			root = deleteNode(root, val);
			for (long long k = 1; k < tests; ++k)
				deleteNode(root, val);

		}
		auto end_time = std::chrono::high_resolution_clock::now();
		auto duration_time = (long double)std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();

		while (size(root) > (n-(i+interval)))
			root = deleteNode(root, (rand()%max_rand));
*/
		std::cout << "For n=" << n-i << ", it takes " << std::setprecision(18) << duration_time/(interval*tests) << " microseconds to delete a key" << std::endl;
		file << std::fixed << std::setprecision(18) << duration_time / (interval*tests)  << std::endl;
	}

	file.close();
}

bool validate(int argc, char *argv[]) {
	
	if (argc < 3) {
		std::cerr << "Too few arguments, you must give the amount of data, and whether or not you are a human" << std::endl;
		return false;
	}

	if (strcmp(argv[2], "1") && strcmp(argv[2], "0")) {
		std::cerr << "Invalid second argument, it must be either 0 or 1" << std::endl;
		return false;
	}
	return true;
}
