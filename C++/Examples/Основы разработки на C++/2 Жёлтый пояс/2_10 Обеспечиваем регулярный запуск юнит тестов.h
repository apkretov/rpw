#pragma once

#include <map>
#include <set>
#include <string>

using Synonyms = std::map<std::string, std::set<std::string>>; 
//MINE using Synonyms = std::map<std::string, std::set<std::string>, std::less<>>; 

void AddSynonyms(Synonyms &synonyms, const std::string &first_word, const std::string &second_word) {
	synonyms[first_word].insert(second_word); // второе слово добавляем в список синонимов первого...
	synonyms[second_word].insert(first_word); // и наоборот
}

size_t GetSynonymCount(Synonyms &synonyms, const std::string &first_word) {
	return synonyms[first_word].size();
}

bool AreSynonyms(Synonyms &synonyms, const std::string &first_word, const std::string &second_word) {
	return synonyms[first_word].contains(second_word); //ORIG return synonyms[first_word].count(second_word) == 1;
}