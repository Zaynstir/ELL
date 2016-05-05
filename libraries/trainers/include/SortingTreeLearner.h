////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  Embedded Machine Learning Library (EMLL)
//  File:     SortingTreeLearner.h (trainers)
//  Authors:  Ofer Dekel
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

// dataset
#include "RowDataset.h"
#include "DenseDataVector.h"

// predictors
#include "DecisionTree.h"

// stl
#include <queue>

namespace trainers
{
    template <typename LossFunctionType>
    class SortingTreeLearner
    {
    public:

        /// <summary> Constructs an instance of SortingTreeLearner. </summary>
        ///
        /// <param name="lossFunction"> The loss function. </param>
        SortingTreeLearner(LossFunctionType lossFunction);

        /// <summary> Trains a decision tree. </summary>
        ///
        /// <typeparam name="ExampleIteratorType"> Type of the example iterator. </typeparam>
        /// <param name="exampleIterator"> [in,out] The example iterator. </param>
        ///
        /// <returns> A decision tree. </returns>
        template <typename ExampleIteratorType>
        predictors::DecisionTree Train(ExampleIteratorType exampleIterator);

    private:
        // struct used to keep statistics about tree leaves
        struct Sums
        {
            double sumWeights = 0;
            double sumWeightedLabels = 0;

            Sums operator-(const Sums& other) const; 
        };

        // struct used to keep info about the gain maximizing split of each leaf in the tree
        struct SplitCandidate
        {
            predictors::DecisionTree::Child* leaf;
            predictors::DecisionTree::SplitRule splitRule;
            double gain = 0;
            uint64_t fromRowIndex;
            uint64_t negativeSize;
            uint64_t positiveSize;
            Sums negativeSums;
            Sums positiveSums;

            bool operator<(const SplitCandidate& other) const { return gain > other.gain; }
        };

        template <typename ExampleIteratorType>
        Sums LoadData(ExampleIteratorType exampleIterator);
        void AddSplitCandidateToQueue(predictors::DecisionTree::Child* leaf, uint64_t fromRowIndex, uint64_t size, Sums sums);
        void SortDatasetByFeature(uint64_t featureIndex, uint64_t fromRowIndex, uint64_t size);
        double CalculateGain(Sums negativeSums, Sums positiveSums) const;
        double GetLeafOutputValue(Sums sums) const;
        void Cleanup();

        LossFunctionType _lossFunction;
        dataset::RowDataset<dataset::DoubleDataVector> _dataset;
        std::priority_queue<SplitCandidate> _queue;
    };
}

#include "../tcc/SortingTreeLearner.tcc"
