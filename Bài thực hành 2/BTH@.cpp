#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;


class phuong_tien {
private:
    int ma_xe;
    string loai_xe;
    int gio_vao;
    int tg_do;

public:
    phuong_tien();
    phuong_tien(int ma, string loai, int gio, int tg);

    int lay_ma_xe() const;
    string lay_loai_xe() const;
    double tinh_phi() const;
    void hien_thi() const;
};

phuong_tien::phuong_tien() : ma_xe(0), loai_xe(""), gio_vao(0), tg_do(0) {}
phuong_tien::phuong_tien(int ma, string loai, int gio, int tg)
    : ma_xe(ma), loai_xe(loai), gio_vao(gio), tg_do(tg) {}

int phuong_tien::lay_ma_xe() const { return ma_xe; }
string phuong_tien::lay_loai_xe() const { return loai_xe; }

double phuong_tien::tinh_phi() const {
    double gia = (loai_xe == "Car") ? 6.0 : (loai_xe == "Motorcycle") ? 4.0 : 2.0;
    bool cao_diem = (gio_vao >= 6 && gio_vao <= 9) || (gio_vao >= 15 && gio_vao <= 18);
    double tong = 0;
    for (int h = 0; h < tg_do; ++h) {
        if (h < 2) tong += gia * (cao_diem ? 1.30 : 0.95);
        else       tong += gia * 0.90;
    }
    return tong;
}

void phuong_tien::hien_thi() const {
    cout << "  ID: " << ma_xe << " | " << loai_xe
         << " | " << gio_vao << "h | " << tg_do << "h"
         << " | Phi: $" << fixed << setprecision(2) << tinh_phi() << "\n";
}


class bai_xe {
private:
    int ma_bai;
    char kich_thuoc;
    static const int SO_XE_TOI_DA = 3;
    phuong_tien danh_sach_xe[SO_XE_TOI_DA]; 
    int so_luong_xe;                       

public:
    bai_xe();
    bai_xe(int ma, char kt);

    int lay_ma() const;
    char lay_kich_thuoc() const { return kich_thuoc; }
    int lay_so_luong_xe() const { return so_luong_xe; }
    phuong_tien lay_xe_tai(int chi_so) const { return danh_sach_xe[chi_so]; }
    
    bool da_day() const;
    bool them(phuong_tien v);
    bool xoa(int ma_xe);
    bool chua(int ma_xe) const;
    void hien_thi() const;
};

bai_xe::bai_xe() : ma_bai(0), kich_thuoc('S'), so_luong_xe(0) {}
bai_xe::bai_xe(int ma, char kt) : ma_bai(ma), kich_thuoc(kt), so_luong_xe(0) {}

int bai_xe::lay_ma() const { return ma_bai; }

bool bai_xe::da_day() const {
    int cap = (kich_thuoc == 'S') ? 1 : (kich_thuoc == 'M') ? 2 : 3;
    return so_luong_xe >= cap;
}

bool bai_xe::them(phuong_tien v) {
    if (da_day()) return false;
    danh_sach_xe[so_luong_xe] = v;
    so_luong_xe++;
    return true;
}

bool bai_xe::xoa(int ma_xe) {
    int vi_tri = -1;
    for (int i = 0; i < so_luong_xe; ++i) {
        if (danh_sach_xe[i].lay_ma_xe() == ma_xe) {
            vi_tri = i;
            break;
        }
    }
    if (vi_tri == -1) return false;
    
    for (int i = vi_tri; i < so_luong_xe - 1; ++i) {
        danh_sach_xe[i] = danh_sach_xe[i + 1];
    }
    so_luong_xe--;
    return true;
}

bool bai_xe::chua(int ma_xe) const {
    for (int i = 0; i < so_luong_xe; ++i) {
        if (danh_sach_xe[i].lay_ma_xe() == ma_xe) return true;
    }
    return false;
}

void bai_xe::hien_thi() const {
    int cap = (kich_thuoc == 'S') ? 1 : (kich_thuoc == 'M') ? 2 : 3;
    cout << "Bai " << ma_bai << " [" << kich_thuoc << "] "
         << so_luong_xe << "/" << cap << " xe\n";
    for (int i = 0; i < so_luong_xe; ++i) {
        danh_sach_xe[i].hien_thi();
    }
}

class SystemInterface {
private:
    static const int SO_BAI_TOI_DA = 10;
    bai_xe danh_sach_bai[SO_BAI_TOI_DA];
    int so_luong_bai;                  
    
    int nhap_so_nguyen() {
        int gia_tri;
        while (!(cin >> gia_tri)) {
            cout << "Loi kieu du lieu! Vui long nhap lai: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        return gia_tri;
    }
    
    bool trung_ma_bai(int ma) const {
        for (int i = 0; i < so_luong_bai; ++i) {
            if (danh_sach_bai[i].lay_ma() == ma) return true;
        }
        return false;
    }
    
    bool trung_ma_xe(int ma) const {
        for (int i = 0; i < so_luong_bai; ++i) {
            if (danh_sach_bai[i].chua(ma)) return true;
        }
        return false;
    }
    
    int sinh_ma_ngau_nhien() const {
        return rand() % 9000 + 1000;
    }

public:
    SystemInterface();
    void runMenu();
};

SystemInterface::SystemInterface() : so_luong_bai(0) {
    srand((unsigned)time(NULL));
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
        cout << "Chon: ";
        chon = nhap_so_nguyen();
        
        switch (chon) {
        case 1: {
            if (so_luong_bai >= SO_BAI_TOI_DA) {
                cout << "Da dat toi da " << SO_BAI_TOI_DA << " bai do!\n";
                break;
            }
            int ma; char kt;
            cout << "Ma bai: "; ma = nhap_so_nguyen();
            if (trung_ma_bai(ma)) {
                cout << "Trung ma bai! ";
                ma = sinh_ma_ngau_nhien();
                while (trung_ma_bai(ma)) ma = sinh_ma_ngau_nhien();
                cout << "Tu dong gan ma ngau nhien: " << ma << "\n";
            }
            cout << "Kich thuoc (S/M/L): "; cin >> kt;
            kt = toupper(kt);
            
            danh_sach_bai[so_luong_bai] = bai_xe(ma, kt);
            so_luong_bai++;
            cout << "Da tao bai " << ma << "\n";
            break;
        }
        case 2: {
            if (so_luong_bai == 0) {
                cout << "Chua co bai do nao!\n";
                break;
            }
            int ma, gio, tg; string loai;
            cout << "Ma xe: "; ma = nhap_so_nguyen();
            if (trung_ma_xe(ma)) {
                cout << "Trung ma xe! ";
                ma = sinh_ma_ngau_nhien();
                while (trung_ma_xe(ma)) ma = sinh_ma_ngau_nhien();
                cout << "Tu dong gan ma ngau nhien: " << ma << "\n";
            }
            cout << "Loai (Car/Motorcycle/Bicycle): "; cin >> loai;
            cout << "Gio vao (0-23): "; gio = nhap_so_nguyen();
            cout << "Thoi luong (1-23): "; tg = nhap_so_nguyen();
            
            phuong_tien v(ma, loai, gio, tg);
            bool ok = false;
            for (int i = 0; i < so_luong_bai; ++i) {
                if (danh_sach_bai[i].them(v)) {
                    ok = true;
                    cout << "Da them xe " << ma << " vao Bai " << danh_sach_bai[i].lay_ma() 
                         << " | Phi: $" << fixed << setprecision(2) << v.tinh_phi() << "\n";
                    break;
                }
            }
            if (!ok) cout << "Tat ca bai da day!\n";
            break;
        }
        case 3: {
            int ma;
            cout << "Ma bai can xoa: "; ma = nhap_so_nguyen();
            int vi_tri = -1;
            for (int i = 0; i < so_luong_bai; ++i) {
                if (danh_sach_bai[i].lay_ma() == ma) {
                    vi_tri = i;
                    break;
                }
            }
            if (vi_tri != -1) {
                for (int i = vi_tri; i < so_luong_bai - 1; ++i) {
                    danh_sach_bai[i] = danh_sach_bai[i + 1];
                }
                so_luong_bai--;
                cout << "Da xoa bai " << ma << "\n";
            } else {
                cout << "Khong tim thay bai!\n";
            }
            break;
        }
        case 4: {
            int ma;
            cout << "Ma xe can lay ra: "; ma = nhap_so_nguyen();
            bool ok = false;
            for (int i = 0; i < so_luong_bai; ++i) {
                if (danh_sach_bai[i].xoa(ma)) {
                    ok = true;
                    break;
                }
            }
            cout << (ok ? "Da lay xe ra\n" : "Khong tim thay xe\n");
            break;
        }
        case 5: {
            if (so_luong_bai == 0) cout << "Khong co bai do nao.\n";
            for (int i = 0; i < so_luong_bai; ++i) {
                danh_sach_bai[i].hien_thi();
            }
            break;
        }
        case 6: {
            int ma;
            cout << "Ma bai: "; ma = nhap_so_nguyen();
            bool ok = false;
            for (int i = 0; i < so_luong_bai; ++i) {
                if (danh_sach_bai[i].lay_ma() == ma) {
                    danh_sach_bai[i].hien_thi();
                    ok = true;
                    break;
                }
            }
            if (!ok) cout << "Khong tim thay bai!\n";
            break;
        }
        case 7: {
            string loai;
            cout << "Loai xe: "; cin >> loai;
            bool co = false;
            for (int i = 0; i < so_luong_bai; ++i) {
                bool in_ten_bai = false;
                for (int j = 0; j < danh_sach_bai[i].lay_so_luong_xe(); ++j) {
                    if (danh_sach_bai[i].lay_xe_tai(j).lay_loai_xe() == loai) {
                        if (!in_ten_bai) {
                            cout << "-> Thuoc bai do " << danh_sach_bai[i].lay_ma() << "\n";
                            in_ten_bai = true;
                            co = true;
                        }
                        danh_sach_bai[i].lay_xe_tai(j).hien_thi();
                    }
                }
            }
            if (!co) cout << "Khong co xe loai nay!\n";
            break;
        }
        case 8: {
            string loai_arr[3] = { "Car", "Motorcycle", "Bicycle" };
            for (int t = 0; t < 3; ++t) {
                int dem = 0; double tong = 0;
                for (int i = 0; i < so_luong_bai; ++i) {
                    for (int j = 0; j < danh_sach_bai[i].lay_so_luong_xe(); ++j) {
                        if (danh_sach_bai[i].lay_xe_tai(j).lay_loai_xe() == loai_arr[t]) {
                            dem++;
                            tong += danh_sach_bai[i].lay_xe_tai(j).tinh_phi();
                        }
                    }
                }
                cout << loai_arr[t] << ": ";
                if (dem == 0) cout << "khong co xe\n";
                else cout << dem << " xe | TB: $" << fixed << setprecision(2) << tong / dem << "\n";
            }
            break;
        }
        case 9:
            return;
        default:
            cout << "Lua chon khong hop le!\n";
            break;
        }
    }
}

int main() {
    SystemInterface sys;
    sys.runMenu();
    return 0;
}
