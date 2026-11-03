// ConsoleApplication3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <string>
using namespace std;
class phuongTien {
private:
    int maXe;
    string loaiXe;
    int gioVaoBai;
    int gioDoDuKien;
    double phiDo;
    bool chuaSoThuc;
public:
    phuongTien() : maXe(0), loaiXe(""), gioVaoBai(0), gioDoDuKien(0), phiDo(0.0), chuaSoThuc(false) {}
    phuongTien(int maXe, string loaiXe, int gioVaoBai, int gioDoDuKien, double phiDo, bool chuaSoThuc);
    double tinhPhi() const;
    void hienThiThongTin() const;
    int lay_ma_xe() const;
    string lay_loai_xe() const;
};
/*double tinhPhi() const {
    if (phuongTien::loaiXe == "xe may") {
          phuongTien::phiDo=gioDoDuKien * 1000;
    }
    return phuongTien::phiDo;
}
int lay_ma_xe() const {
	return maXe;
}*/
class bai_xe {
private:
    int ma_bai;
    char kich_thuoc;
    phuongTien[]; pt1, pt2, pt3;   // sau này dùng mảng
    bool co1, co2, co3;

public:
    bai_xe();
    bai_xe(int ma, char kt);

    int lay_ma() const;
    bool them(phuongTien v);
    bool xoa(int maXe);
    bool chua(int maXe ) const;
    void hien_thi() const;
    bool co_loai(string loai, int& dem, double& tong) const;
};


int main()
{
    cout << "Hello World!\n";
}


