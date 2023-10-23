#include "interval_map.hh"
#include <stdio.h>
#include <limits>

// constructor associates whole range of K with val
template<typename K, typename V>
interval_map<K,V>::interval_map(V const& val)
: m_valBegin(val)
{

}

// Assign value val to interval [keyBegin, keyEnd).
// Overwrite previous values in this interval.
// Conforming to the C++ Standard Library conventions, the interval
// includes keyBegin, but excludes keyEnd.
// If !( keyBegin < keyEnd ), this designates an empty interval,
// and assign must do nothing.
template<typename K, typename V>
void interval_map<K,V>::assign( K const& keyBegin, K const& keyEnd, V const& val ) {
	// INSERT YOUR SOLUTION HERE
	K valueTempEnd = 0;//Value used to know which iteration was before and insert it at the end
	if(keyBegin < keyEnd){
		//Valid Interval, insert values:


		// Insert the new interval [keyBegin, keyEnd) into the map.
	    // First, remove any overlapping intervals.
	    //we store the it lowerBound of the keyBegin to process
	    auto it = m_map.lower_bound(keyBegin);
	    /* We need to do keyBegin - 1 to search for previous iterations in order to continue 
	    them after, in case this interval is inside a bigger one */
	    auto itEnd = m_map.lower_bound(keyBegin - 1);
		

	    /* In case the end is the initial character m_valBegin, we need to get the previous */
	    if(itEnd->second == m_valBegin)
	    	itEnd = std::prev(itEnd);
	    /* In case the iteration that 'ends' is exactly the same as the start 
	    dont need to update. The end is the VAL */
	    if(itEnd->first == keyBegin){
	    	valueTempEnd = val;
	    }
	    else{/* Else we need to update the new iteration end */
	    	valueTempEnd = itEnd->second;//Finished processing, store value
	    }

	    //check for the iteration (we found one!)
	    if (it != m_map.begin()) {
	        --it;  
	    }

	    while (it != m_map.end() && it->first < keyEnd) {
	    	// In case we found an iteration we need to modify the actual range (delete iterations inside)
	        auto next = std::next(it);//Cycle.
	        if (it->second != val) {
	            if (it->first < keyBegin) {	            	
	            	//Insert new iteration
	                m_map.insert_or_assign(it, keyBegin, val);
	                it = m_map.lower_bound(keyBegin);
	            }
	            else if (it->first < keyEnd) {
	            	//Erase other iterations.
	                m_map.erase(it);
	                
	            } 
	        }
	        it = next;
	    }

	    // Insert the new interval [keyBegin, keyEnd).
	    if (m_map.empty() || (m_valBegin != val && 
	     (itEnd->first < keyBegin || keyBegin < itEnd->first)/*m_map.begin()->first != keyBegin*/)) {
	        m_map.insert_or_assign(m_map.lower_bound(keyBegin), keyBegin, val);
	    }


	    //Now insert the last values to end cycle of iteration.
	    if(it == m_map.end()){
	    	//Insert the start of m_valBegin to mark the end, since now iteration was found previuosly
	       	m_map.insert_or_assign(m_map.lower_bound(keyEnd), keyEnd, m_valBegin);
	    }
	    else{
	       	//Insert the value of the temporal End calculated and the start to end cycle.
	       	m_map.insert_or_assign(m_map.lower_bound(keyEnd), keyEnd, valueTempEnd);
	    }
	}
}

// look-up of the value associated with key
template<typename K, typename V>
V const& interval_map<K,V>::operator[]( K const& key ) const {
	auto it=m_map.upper_bound(key);
	if(it==m_map.begin()) {
		return m_valBegin;
	} else {
		return (--it)->second;
	}
}

// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a test function that tests the functionality of
// the interval_map, for example using a map of int intervals to char.

/*void TemporaryFunction ()
{
    interval_map<int,char> TempObj('A');
}*/