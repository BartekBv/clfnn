#pragma once
#include <fstream>

/**
 * @brief Interface for layers that can save and load their state.
 * Defines the binary serialization operations needed to persist a layer's
 * parameters to disk and restore them later. Only layers with state worth
 * persisting (e.g. `DenseLayer`) need to implement this, keeping stateless
 * layers free of unused method implementations.
 */

class IPersistableLayer {
    public:
        virtual ~IPersistableLayer() = default;
        virtual void save(std::ofstream& out) const = 0;
        virtual void load(std::ifstream& in) = 0;
};
