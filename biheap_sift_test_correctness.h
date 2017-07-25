/*
 * biheap_sift_test_correctness.h
 *
 *  Created on: Jul 25, 2017
 *      Author: diagoras
 */

#ifndef BIHEAP_SIFT_TEST_CORRECTNESS_H_
#define BIHEAP_SIFT_TEST_CORRECTNESS_H_

#include <random>
#include "random_helpers.h"
#include "biheapify.h"
#include "biheap_sift.h"

template<class T>
bool BiHeapSiftTestCorrectness(long start_total_num_nodes,
                               long end_total_num_nodes,
                               long num_vecs_to_try = 1,
                               long increment_size = 1) {
  int total_num_nodes = start_total_num_nodes;
  while (total_num_nodes <= end_total_num_nodes) {
    std::vector<T> vec(total_num_nodes + 1);
    for (auto vec_counter = 0l; vec_counter < num_vecs_to_try; vec_counter++) {
      randomhelpers::FillWithRandomNumbers(vec.begin(), vec.end(),
                0, static_cast<T>(4*total_num_nodes));//std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
      size_type pos_hc;
      {
        std::random_device rnd_device;
        std::mt19937 generator(rnd_device());
        std::uniform_int_distribution<T> dist(0, total_num_nodes - 1);
        pos_hc = dist(generator);
      }
      //Form a biheap.
      BiHeapify(vec.begin(), total_num_nodes);
      //Change one randomly selected element to some random value (which was
      // stored outside of the biheap in vec[total_num_nodes]).
      vec[pos_hc] = vec[total_num_nodes];
      //Sift the changed element.
      BiHeapSift(vec.begin(), total_num_nodes, pos_hc);
      //Check that we once again have a biheap.
      bool is_biheap = IsBiheap(vec.begin(), total_num_nodes);
      if (!is_biheap) {
        std::cout << "Sift() failed to form a biheap. "
                  << "total_num_nodes = " << total_num_nodes << std::endl;
        return false;
      }
    }
  }
  return true;
}

#endif /* BIHEAP_SIFT_TEST_CORRECTNESS_H_ */
