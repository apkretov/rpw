void vectorOutput(const vector<unsigned int> &myvector) {
	cout << "myvector contains:";
	for (int i=0; i<myvector.size(); i++)
		cout << " " << myvector[i];
	cout << endl << "myvector capacity: " << myvector.capacity() << endl;
	cout << endl << endl;
}

void test() {
	unsigned int i;
	vector<unsigned int> myvector;
	cout << endl << "myvector capacity: " << myvector.capacity() << endl;
	for (i=1; i<=10; i++) myvector.push_back(i);  // set some values (from 1 to 10)
	vectorOutput(myvector);
	for (i=10; i<=20; i++) myvector.push_back(i);  // set some values (from 1 to 10)
	vectorOutput(myvector);
	myvector.reserve(20);
	vectorOutput(myvector);
	myvector.erase (myvector.begin()+5); // erase the 6th element
	myvector.erase (myvector.begin(),myvector.begin()+3);   // erase the first 3 elements:
	vectorOutput(myvector);
	myvector.resize(7);
	vectorOutput(myvector);
	cout << endl;
}
