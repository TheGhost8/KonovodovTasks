#include "factory.h"

class TFactory::TImpl {
	class ICreator {
	public:
		virtual ~ICreator(){}
		virtual TGeneratorPtr Create(const TOptions& opts) const = 0;
	};

	using TCreatorPtr = std::shared_ptr<ICreator>;
	using TRegisteredCreators =	std::map<std::string, TCreatorPtr>;

	TRegisteredCreators RegisteredCreators;

public:
	template <class TCurrentObject>
	class TCreator : public ICreator{
		TGeneratorPtr Create(const TOptions& opts) const override{
			return std::make_unique<TCurrentObject>(opts);
		}
	};

	TImpl() {
		RegisterAll();
	}

	template <typename T>
	void RegisterCreator(const std::string& name) {
		RegisteredCreators[name] = std::make_shared<TCreator<T>>();
	}
	
	void RegisterAll() {
		RegisterCreator<IRandomPoissonGenerator>("poisson");
		RegisterCreator<IRandomBernoulliGenerator>("bernoulli");
		RegisterCreator<IRandomGeometricGenerator>("geometric");
		RegisterCreator<IRandomFiniteGenerator>("finite");
	}

	TGeneratorPtr CreateObject(const std::string& n, const TOptions& opts) const {
		double sum = 0;
		auto creator = RegisteredCreators.find(n);
		if (creator == RegisteredCreators.end()) {
			return nullptr;
		}
		if ((n == "poisson") && (opts.GetDistributionParam() <= 0.0)) {
			return nullptr;
		}
		if (((n == "bernoulli") || (n == "geometric")) && (!((opts.GetDistributionParam() >= 0.0) && (opts.GetDistributionParam() <= 1.0)))) {
			return nullptr;	
		}
		if (n == "finite") {
			if (opts.GetDistributionValues().size() != opts.GetDistributionProbabilities().size()) {
				return nullptr;
			}
			for (auto& p : opts.GetDistributionProbabilities()) {
				if (!((p >= 0.0) && (p <= 1.0))) {
					return nullptr;
				}
				sum += p;
			}
			if (sum != 1.0) {
				return nullptr;
			}
		}
		return creator->second->Create(opts);
	}

	std::vector<std::string> GetAvailableObjects () const {
		std::vector<std::string> result;
		for (const auto& creatorPair : RegisteredCreators) {
			result.push_back(creatorPair.first);
		}
		return result;
	}
};

TFactory::TFactory() : Impl(std::make_unique<TFactory::TImpl>()) {}

TGeneratorPtr TFactory::CreateGenerator(const std::string& n, const TOptions& opts) const {
	return Impl->CreateObject(n, opts);
}

std::vector<std::string> TFactory::GetAvailableObjects() const {
	return Impl->GetAvailableObjects();
}

double CheckGenerate(TGeneratorPtr* pGenerator) {
	double sample_mean = 0.0;
	size_t sample_size = 10000;
	for (size_t i = 0; i < sample_size; ++i) {
		sample_mean += (*pGenerator)->Generate();
	}
	return sample_mean / sample_size;
}

int main() {
	std::map<std::string, double> theoretical_means = {{"poisson", 0.5}, {"bernoulli", 0.5}, {"geometric", 1.0}, {"finite", 2.6}};
    TFactory hFactory;
    TOptions opts(0.5, {1, 3}, {0.2, 0.8});
    TGeneratorPtr pGenerator;
    std::vector<std::string> availableobj = hFactory.GetAvailableObjects();

    for (auto& s : availableobj) {
    	pGenerator = hFactory.CreateGenerator(s, opts);
    	std::cout << s << "\n\ttheoretical mean: " << std::to_string(theoretical_means[s]) << "\n\tsample mean: " << std::to_string(CheckGenerate(&pGenerator)) << std::endl;
    }
}