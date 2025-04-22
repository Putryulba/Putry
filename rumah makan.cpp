#include <iostream>
using namespace std;

int main(){
	int jarak,ongkir,jumlah;
	
	cout << "Jarak ke rumah anda: "<<endl;
	cin>>jarak;
	if(jarak <= 3){
		cout << "Biaya ongkir ke rumah anda : " << endl;
		cin >> ongkir;
	} else {
		cout << "Biaya ongkir ke rumah anda : " << endl;
		cin >> ongkir;
	}
	
	cout << "===== SLIP PEMBAYARAN =====" << endl;
	cout << "makan" << endl;
	cout << "Jumlah pesanan			: " << jumlah << endl;
	cout << "jarak ke rumah anda	: " << jarak << endl;
	cout << "Harga ongkir			: " << ongkir << endl << endl;
	cout << "			TERIMAKASIH			" << endl;
	cout << "=====================================================" << endl;
	
	return 0;	
}
