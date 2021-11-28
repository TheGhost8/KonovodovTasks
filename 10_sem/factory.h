#pragma once

#include <stdio.h>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <random>

static std::random_device rd;
static std::mt19937 gen(rd());

class TOptions {
	double distribution_param;
	std::vector<size_t> values;
	std::vector<double> probabilities;

public:
	TOptions(double new_distribution_param) : distribution_param(new_distribution_param) {};
	TOptions(const std::vector<size_t>& new_values, const std::vector<double>& new_probabilities) : values(new_values), probabilities(new_probabilities) {};
	TOptions(double new_distribution_param,
			 const std::vector<size_t>& new_values,
			 const std::vector<double>& new_probabilities) : distribution_param(new_distribution_param), values(new_values), probabilities(new_probabilities) {};

	double GetDistributionParam() const {
		return distribution_param;
	}

	std::vector<size_t> GetDistributionValues() const {
		return values;
	}

	std::vector<double> GetDistributionProbabilities() const {
		return probabilities;
	}
};

class TRandomNumberGenerator {	
public:
	virtual ~TRandomNumberGenerator() {};
	virtual double Generate() = 0;
};

using TGeneratorPtr = std::unique_ptr<TRandomNumberGenerator>;

class IRandomPoissonGenerator : public TRandomNumberGenerator {
	std::poisson_distribution<int> randomGenerator;

public:
	IRandomPoissonGenerator(const TOptions& params) {
		randomGenerator = std::poisson_distribution<int>(params.GetDistributionParam());
	};
	double Generate() override {
		return (double)randomGenerator(gen);
		//std::cout << std::to_string(lambda) << std::endl;
	};
};

class IRandomBernoulliGenerator : public TRandomNumberGenerator {
	std::bernoulli_distribution randomGenerator;

public:
	IRandomBernoulliGenerator(const TOptions& params) : randomGenerator(params.GetDistributionParam()) {};
	double Generate() override {
		return (double)randomGenerator(gen);
		//std::cout << std::to_string(p) << std::endl;
	};
};

class IRandomGeometricGenerator : public TRandomNumberGenerator {
	std::geometric_distribution<int> randomGenerator;

public:
	IRandomGeometricGenerator(const TOptions& params) : randomGenerator(params.GetDistributionParam()) {};
	double Generate() override {
		return (double)randomGenerator(gen);
		//std::cout << std::to_string(p) << std::endl;
	};
};

class IRandomFiniteGenerator : public TRandomNumberGenerator {
	std::vector<size_t> values;
	std::vector<double> probabilities;
	std::discrete_distribution<int> randomGenerator;

public:
	IRandomFiniteGenerator(const TOptions& params) : values(params.GetDistributionValues()), probabilities(params.GetDistributionProbabilities()) {
		std::vector<double> real_probabilities;
		for (size_t i = 0; i < values.size(); ++i) {
			while (real_probabilities.size() < values[i]) {
				real_probabilities.push_back(0.0);
			}
			real_probabilities.push_back(probabilities[i]);
		}
		randomGenerator = std::discrete_distribution<int>(real_probabilities.begin(), real_probabilities.end());
	};
	double Generate() override {
		/*
		for (size_t i = 0; i < values.size(); ++i) {
			std::cout << std::to_string(values[i]) << ": " << std::to_string(probabilities[i]) << std::endl;
		}
		*/
		return (double)randomGenerator(gen);
	};
};

class TFactory {
	class TImpl;
	std::unique_ptr<const TImpl> Impl;

public:
	TFactory();
	~TFactory() {};
	TGeneratorPtr CreateGenerator(const std::string& name, const TOptions& opts) const;
	std::vector<std::string> GetAvailableObjects() const;
};