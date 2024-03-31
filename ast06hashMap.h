// assignment is to implement a banking account matching system using hash maps 

#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>

using namespace std; 

template <class t1, class t2>
class hashMap
{
public:
	hashMap(std::size_t = 5);
	t2& operator[](t1);
private:
	struct keyVal
	{
		keyVal()
		{
			key = t1();
			value = t2();
		}

		t1 key;
		t2 value;
	};

	void resize(std::size_t);

	std::size_t hash1(std::string);
	std::size_t hash2(std::string);

	std::vector<keyVal> table1;
	std::vector<keyVal> table2;

	std::size_t items1;
	std::size_t items2;
};

template <class t1, class t2>
hashMap<t1, t2>::hashMap(std::size_t size)
{
	for(int i = 0; i < size; i++){
		table1.emplace_back(); 
		table2.emplace_back(); 
	}
}

template <class t1, class t2>
t2& hashMap<t1, t2>::operator[](t1 key)
{
	// determine load factor 
	double items1Dbl = static_cast<double>(items1); 
	double items2Dbl = static_cast<double>(items2); 
	double loadFactorT1 = items1Dbl / table1.size(); 
	int table1size = table1.size(); // for debugging 
	double loadFactorT2 = items2Dbl / table2.size(); 
	if(loadFactorT1 > 0.20 || loadFactorT2 > 0.20){
		this->resize(table1.size()); 
	}
	std::size_t index1 = hash1(key) % table1.size();
	std::size_t index2 = hash2(key) % table2.size();

	// initialize collision counters 
	int i1 = 0; 
	int i2 = 0; 

	int iterations = 0; // used for tracking even and odd iterations in case of collision 
	while(true){
		
		if(table1[index1].key == t1()){ //then we have a blank space 
			table1[index1].key = key; 
			items1++; 
			return table1[index1].value; 
		}
		
		if(table1[index1].key == key){ //if we have a match 
			return table1[index1].value; 
		}

		// if control has reached here, then begin checking table 2 

		if(table2[index2].key == t1()){ //then we have a blank space 
			table2[index2].key = key; 
			items2++; 
			return table2[index2].value; 
		}
		
		if(table2[index2].key == key){ //if we have a match 
			return table2[index2].value; 
		} 

		// if control has reached here, collision has occured 
		// increment collision counters 
		i1++; 
		i2++; 

		if(iterations % 2 == 0){  // then iteration is even 
			index1 = ( (index1 + i1) * hash2(key)) % table1.size();
			index2 = ( (index2 + i2) * hash1(key)) % table2.size(); 
		}else {
			index1 = ( (index1 + i1) * hash1(key)) % table1.size();
			index2 = ( (index2 + i2) * hash2(key)) % table2.size(); 
		}

		iterations++; //change from even to odd and vice versa 
	} 
	
	


}

template <class t1, class t2>
void hashMap<t1, t2>::resize(std::size_t amount)
{
	//save old table sizes so we can have access to old indices while still resizing vectors 
	vector<keyVal> tempTable1 = table1; 
	vector<keyVal> tempTable2 = table2;
	
	//clear old hash table
	for(int i = 0; i < table1.size(); i++){
		table1[i] = keyVal(); 
		table2[i] = keyVal(); 
	}
	items1 = 0; // must reset items to zero since we emptied has table contents 
	items2 = 0; 
	// resize by specified amount by inserting blank elements 
	for(int i = 0; i < amount; i++){
		table1.emplace_back(); 
		table2.emplace_back(); 
	}
	

	//go through and rehash now 
	for(int i = 0; i < tempTable1.size(); i++){
		if(tempTable1[i].key != t1()){ // if value at index is not blank, then rehash 
			//(*this)[tempTable1[i].key]; 
			//(*this)[tempTable1[i].key] = tempTable1[i].value; 
			(*this)[tempTable2[i].key] = tempTable2[i].value; 
		}
		if(tempTable2[i].key != t1()){ // if value at index is not blank, then rehash 
			//(*this)[tempTable2[i].key]; 
			//(*this)[tempTable2[i].key] = tempTable2[i].value;
			(*this)[tempTable2[i].key] = tempTable2[i].value; 
		}
	}

}

template <class t1, class t2>
std::size_t hashMap<t1, t2>::hash1(std::string key)
{
	int h1Sum = 0; 
	for(int i = 0; i < key.size(); i++){
		h1Sum = h1Sum + (key[i] * pow(10, i)); 
	}

	return h1Sum; 

}

template <class t1, class t2>
std::size_t hashMap<t1, t2>::hash2(std::string key)
{
	int h2Sum = 0; 
	int k = key.length(); 
	for(int i = 0; i < key.size(); i++){
		h2Sum = h2Sum + (key[k-1-i] * pow(10, i)); 
	}

	return h2Sum; 
}
