#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class phuong_tien {
private:
    int ma_xe;
    string loai_xe;
    int gio_vao;
    int tg_do;
    double phi_do;

public:
    phuong_tien();
    phuong_tien(int ma, string loai, int gio, int tg);

    int lay_ma_xe() const;
    string lay_loai_xe() const;
    double lay_phi() const;
    
    void nhap();
    double tinh_phi();
    void hien_thi() const;
};

phuong_tien::phuong_tien() {
    ma_xe = 0;
    loai_xe = "";
    gio_vao = 0;
    tg_do = 0;
    phi_do = 0.0;
}

phuong_tien::phuong_tien(int ma, string loai, int gio, int tg) {
    ma_xe = ma;
    loai_xe = loai;
    gio_vao = gio;
    tg_do = tg;
    phi_do = 0.0;
}

int phuong_tien::lay_ma_xe() const { return ma_xe; }
string phuong_tien::lay_loai_xe() const { return loai_xe; }
double phuong_tien::lay_phi() const { return phi_do; }

void phuong_tien::nhap() {
    cout << "Nhap ma xe: ";
    cin >> ma_xe;
    cout << "Nhap loai xe (Car/Motorcycle/Bicycle): ";
    cin >> loai_xe;
    cout << "Nhap gio vao bai (0-23): ";
    cin >> gio_vao;
    cout << "Nhap thoi luong do (1-23 gio): ";
    cin >> tg_do;
}

double phuong_tien::tinh_phi() {
    double gia;
    if (loai_xe == "Car") gia = 6.0;
    else if (loai_xe == "Motorcycle") gia = 4.0;
    else if (loai_xe == "Bicycle") gia = 2.0;
    else gia = 0;

    bool caodiem = (gio_vao >= 6 && gio_vao <= 9) || (gio_vao >= 15 && gio_vao <= 18);
    double tile = caodiem ? 1.30 : 0.95;

    if (tg_do <= 2) {
        phi_do = gia * tile * tg_do;
    } else {
        phi_do = gia * tile * 2 + gia * 0.90 * (tg_do - 2);
    }
    return phi_do;
}

void phuong_tien::hien_thi() const {
    cout << fixed << setprecision(2);
    cout << "Ma xe: " << ma_xe << " | Loai xe: " << loai_xe 
         << " | Gio vao: " << gio_vao << " | Thoi luong do: " << tg_do 
         << " gio | Phi do xe: " << phi_do << " $" << endl;
}

class bai_xe {
private:
    int ma_bai;
    char kich_thuoc;
    phuong_tien pt1, pt2, pt3;
    bool co1, co2, co3;

public:
    bai_xe();
    bai_xe(int ma, char kt);

    int lay_ma() const;
    bool them(const phuong_tien& v);
    bool xoa(int ma_xe);
    bool chua(int ma_xe) const;
    void hien_thi() const;
    bool co_loai(string loai, int& dem, double& tong) const;
};

bai_xe::bai_xe() {
    ma_bai = 0;
    kich_thuoc = 'S';
    co1 = false; co2 = false; co3 = false;
}

bai_xe::bai_xe(int ma, char kt) {
    ma_bai = ma;
    kich_thuoc = kt;
    co1 = false; co2 = false; co3 = false;
}

int bai_xe::lay_ma() const { return ma_bai; }

bool bai_xe::them(const phuong_tien& v) {
    int cap = (kich_thuoc == 'S') ? 1 : (kich_thuoc == 'M') ? 2 : 3;
    if (cap >= 1 && !co1) { pt1 = v; co1 = true; return true; }
    if (cap >= 2 && !co2) { pt2 = v; co2 = true; return true; }
    if (cap >= 3 && !co3) { pt3 = v; co3 = true; return true; }
    return false;
}

bool bai_xe::xoa(int ma_xe) {
    if (co1 && pt1.lay_ma_xe() == ma_xe) {
        if (co2) { pt1 = pt2; if (co3) { pt2 = pt3; co3 = false; } else co2 = false; } else co1 = false;
        return true;
    }
    if (co2 && pt2.lay_ma_xe() == ma_xe) {
        if (co3) { pt2 = pt3; co3 = false; } else co2 = false;
        return true;
    }
    if (co3 && pt3.lay_ma_xe() == ma_xe) { co3 = false; return true; }
    return false;
}

bool bai_xe::chua(int ma_xe) const {
    if (co1 && pt1.lay_ma_xe() == ma_xe) return true;
    if (co2 && pt2.lay_ma_xe() == ma_xe) return true;
    if (co3 && pt3.lay_ma_xe() == ma_xe) return true;
    return false;
}

void bai_xe::hien_thi() const {
    int cap = (kich_thuoc == 'S') ? 1 : (kich_thuoc == 'M') ? 2 : 3;
    int so_xe = co1 + co2 + co3;
    cout << "--- Bai " << ma_bai << " [" << kich_thuoc << "] " << so_xe << "/" << cap << " xe ---\n";
    if (co1) pt1.hien_thi();
    if (co2) pt2.hien_thi();
    if (co3) pt3.hien_thi();
}

bool bai_xe::co_loai(string loai, int& dem, double& tong) const {
    dem = 0; tong = 0;
    if (co1 && pt1.lay_loai_xe() == loai) { ++dem; tong += pt1.lay_phi(); }
    if (co2 && pt2.lay_loai_xe() == loai) { ++dem; tong += pt2.lay_phi(); }
    if (co3 && pt3.lay_loai_xe() == loai) { ++dem; tong += pt3.lay_phi(); }
    return dem > 0;
}

class SystemInterface {
private:
    bai_xe bai1, bai2, bai3;
    bool co1, co2, co3;

public:
    SystemInterface();
    void runMenu();
};

SystemInterface::SystemInterface() {
    co1 = false; co2 = false; co3 = false;
}

void SystemInterface::runMenu() {
    int chon;
    while (true) {
        cout << "\n===== QUAN LY BAI DO XE =====\n";
        cout << "1. Tao bai do\n";
        cout << "2. Them xe\n";
        cout << "3. Xoa bai do\n";
        cout << "4. Lay xe ra\n";
        cout << "5. Hien thi tat ca bai do\n";
        cout << "6. Hien thi xe theo bai\n";
        cout << "7. Liet ke xe theo loai\n";
        cout << "8. Bao cao phi trung binh\n";
        cout << "9. Thoat\n";
        cout << "Chon chuc nang: ";
        cin >> chon;

        if (chon == 1) {
            int ma; char kt;
            cout << "Nhap ma bai do: "; cin >> ma;
            cout << "Nhap kich thuoc (S/M/L): "; cin >> kt;
            
            if (!co1) { bai1 = bai_xe(ma, kt); co1 = true; cout << "Da tao bai 1.\n"; }
            else if (!co2) { bai2 = bai_xe(ma, kt); co2 = true; cout << "Da tao bai 2.\n"; }
            else if (!co3) { bai3 = bai_xe(ma, kt); co3 = true; cout << "Da tao bai 3.\n"; }
            else cout << "He thong da day (toi da 3 bai do)!\n";
        } 
        else if (chon == 2) {
            phuong_tien xe;
            xe.nhap();    
            xe.tinh_phi();  
            
            bool them_xong = false;
            if (co1 && bai1.them(xe)) them_xong = true;
            else if (co2 && bai2.them(xe)) them_xong = true;
            else if (co3 && bai3.them(xe)) them_xong = true;
            
            if (them_xong) cout << "Da them xe vao bai.\n";
            else cout << "Khong the them (het cho hoac khong co bai phu hop)!\n";
        } 
        else if (chon == 3) {
            int ma; cout << "Nhap ma bai can xoa: "; cin >> ma;
            if (co1 && bai1.lay_ma() == ma) { co1 = false; cout << "Da xoa bai 1.\n"; }
            else if (co2 && bai2.lay_ma() == ma) { co2 = false; cout << "Da xoa bai 2.\n"; }
            else if (co3 && bai3.lay_ma() == ma) { co3 = false; cout << "Da xoa bai 3.\n"; }
            else cout << "Khong tim thay bai do co ma nay.\n";
        } 
        else if (chon == 4) {
            int maxe; cout << "Nhap ma xe can lay ra: "; cin >> maxe;
            bool lay_xong = false;
            if (co1 && bai1.xoa(maxe)) lay_xong = true;
            else if (co2 && bai2.xoa(maxe)) lay_xong = true;
            else if (co3 && bai3.xoa(maxe)) lay_xong = true;
            
            if (lay_xong) cout << "Da lay xe khoi bai.\n";
            else cout << "Khong tim thay xe trong he thong.\n";
        } 
        else if (chon == 5) {
            if (co1) bai1.hien_thi();
            if (co2) bai2.hien_thi();
            if (co3) bai3.hien_thi();
            if (!co1 && !co2 && !co3) cout << "Chua co bai do nao.\n";
        } 
        else if (chon == 6) {
            int ma; cout << "Nhap ma bai do: "; cin >> ma;
            if (co1 && bai1.lay_ma() == ma) bai1.hien_thi();
            else if (co2 && bai2.lay_ma() == ma) bai2.hien_thi();
            else if (co3 && bai3.lay_ma() == ma) bai3.hien_thi();
            else cout << "Khong tim thay bai do.\n";
        } 
        else if (chon == 7) {
            string loai; cout << "Nhap loai xe (Car/Motorcycle/Bicycle): "; cin >> loai;
            int d; double t;
            if (co1) { bai1.co_loai(loai, d, t); if (d > 0) bai1.hien_thi(); }
            if (co2) { bai2.co_loai(loai, d, t); if (d > 0) bai2.hien_thi(); }
            if (co3) { bai3.co_loai(loai, d, t); if (d > 0) bai3.hien_thi(); }
        } 
        else if (chon == 8) {
            int d_car = 0, d_moto = 0, d_bike = 0;
            double t_car = 0, t_moto = 0, t_bike = 0;
            int d; double t;
            
            if (co1) { bai1.co_loai("Car", d, t); d_car += d; t_car += t; }
            if (co2) { bai2.co_loai("Car", d, t); d_car += d; t_car += t; }
            if (co3) { bai3.co_loai("Car", d, t); d_car += d; t_car += t; }
            
            if (co1) { bai1.co_loai("Motorcycle", d, t); d_moto += d; t_moto += t; }
            if (co2) { bai2.co_loai("Motorcycle", d, t); d_moto += d; t_moto += t; }
            if (co3) { bai3.co_loai("Motorcycle", d, t); d_moto += d; t_moto += t; }
            
            if (co1) { bai1.co_loai("Bicycle", d, t); d_bike += d; t_bike += t; }
            if (co2) { bai2.co_loai("Bicycle", d, t); d_bike += d; t_bike += t; }
            if (co3) { bai3.co_loai("Bicycle", d, t); d_bike += d; t_bike += t; }
            
            cout << "--- BAO CAO PHI TRUNG BINH ---\n";
            cout << "Car: " << (d_car > 0 ? (t_car / d_car) : 0) << " $\n";
            cout << "Motorcycle: " << (d_moto > 0 ? (t_moto / d_moto) : 0) << " $\n";
            cout << "Bicycle: " << (d_bike > 0 ? (t_bike / d_bike) : 0) << " $\n";
        } 
        else if (chon == 9) {
            cout << "Thoat he thong...\n";
            break;
        } 
        else {
            cout << "Lua chon khong hop le.\n";
        }
    }
}

int main() {
    SystemInterface hethong;
    hethong.runMenu();
    return 0;
}
