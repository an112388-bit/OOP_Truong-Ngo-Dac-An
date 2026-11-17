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
    int thoi_gian_do;

public:
    phuong_tien();
    phuong_tien(int ma, string loai, int gio, int thoi_gian);

    int lay_ma_xe() const;
    string lay_loai_xe() const;
    double tinh_phi() const;
    void hien_thi() const;
};

phuong_tien::phuong_tien() : ma_xe(0), loai_xe(""), gio_vao(0), thoi_gian_do(0) {}

phuong_tien::phuong_tien(int ma, string loai, int gio, int thoi_gian)
    : ma_xe(ma), loai_xe(loai), gio_vao(gio), thoi_gian_do(thoi_gian) {}

int phuong_tien::lay_ma_xe() const { return ma_xe; }
string phuong_tien::lay_loai_xe() const { return loai_xe; }

double phuong_tien::tinh_phi() const {
    double gia_tien = (loai_xe == "Car") ? 6.0 : (loai_xe == "Motorcycle") ? 4.0 : 2.0;
    bool gio_cao_diem = (gio_vao >= 6 && gio_vao <= 9) || (gio_vao >= 15 && gio_vao <= 18);
    double tong_tien = 0;
    
    for (int gio = 0; gio < thoi_gian_do; ++gio) {
        if (gio < 2) tong_tien += gia_tien * (gio_cao_diem ? 1.30 : 0.95);
        else         tong_tien += gia_tien * 0.90;
    }
    return tong_tien;
}

void phuong_tien::hien_thi() const {
    cout << "  ID: " << ma_xe << " | " << loai_xe
         << " | " << gio_vao << "h | " << thoi_gian_do << "h"
         << " | Phi: $" << fixed << setprecision(2) << tinh_phi() << "\n";
}



class bai_xe {
private:
    int ma_bai;
    char kich_thuoc;
    int suc_chua;                     
    int so_luong_xe;
    phuong_tien** danh_sach_xe;       

    void khoi_tao_mang(int suc_chua_ban_dau);

public:
    bai_xe();
    bai_xe(int ma, char kt);

    ~bai_xe();                                      
    bai_xe(const bai_xe& bai_khac);                    
    bai_xe& operator=(const bai_xe& bai_khac);         

    int lay_ma_bai() const;
    char lay_kich_thuoc() const { return kich_thuoc; }
    int lay_suc_chua() const { return suc_chua; }
    int lay_so_luong_xe() const { return so_luong_xe; }
    phuong_tien* lay_xe_tai(int chi_so) const { return danh_sach_xe[chi_so]; }
    
    void mo_rong_suc_chua(int suc_chua_moi);                   
    bool them_xe(const phuong_tien& xe_moi);
    bool xoa_xe(int ma_xe_can_xoa);
    bool chua_xe(int ma_xe_can_tim) const;
    void hien_thi_thong_tin() const;
};

void bai_xe::khoi_tao_mang(int suc_chua_ban_dau) {
    danh_sach_xe = new phuong_tien*[suc_chua_ban_dau];
    for (int i = 0; i < suc_chua_ban_dau; ++i) {
        danh_sach_xe[i] = nullptr;
    }
}

bai_xe::bai_xe() : ma_bai(0), kich_thuoc('S'), suc_chua(1), so_luong_xe(0) {
    khoi_tao_mang(suc_chua);
}

bai_xe::bai_xe(int ma, char kt) : ma_bai(ma), kich_thuoc(kt), so_luong_xe(0) {
    suc_chua = (kich_thuoc == 'S') ? 1 : (kich_thuoc == 'M') ? 2 : 3;
    khoi_tao_mang(suc_chua);
}

bai_xe::~bai_xe() {
    for (int i = 0; i < so_luong_xe; ++i) {
        delete danh_sach_xe[i];
    }
    delete[] danh_sach_xe;
}

bai_xe::bai_xe(const bai_xe& bai_khac) {
    ma_bai = bai_khac.ma_bai;
    kich_thuoc = bai_khac.kich_thuoc;
    suc_chua = bai_khac.suc_chua;
    so_luong_xe = bai_khac.so_luong_xe;
    khoi_tao_mang(suc_chua);
    for (int i = 0; i < so_luong_xe; ++i) {
        danh_sach_xe[i] = new phuong_tien(*(bai_khac.danh_sach_xe[i]));
    }
}

bai_xe& bai_xe::operator=(const bai_xe& bai_khac) {
    if (this != &bai_khac) {
        for (int i = 0; i < so_luong_xe; ++i) delete danh_sach_xe[i];
        delete[] danh_sach_xe;
        
        ma_bai = bai_khac.ma_bai;
        kich_thuoc = bai_khac.kich_thuoc;
        suc_chua = bai_khac.suc_chua;
        so_luong_xe = bai_khac.so_luong_xe;
        khoi_tao_mang(suc_chua);
        for (int i = 0; i < so_luong_xe; ++i) {
            danh_sach_xe[i] = new phuong_tien(*(bai_khac.danh_sach_xe[i]));
        }
    }
    return *this;
}

int bai_xe::lay_ma_bai() const { return ma_bai; }

void bai_xe::mo_rong_suc_chua(int suc_chua_moi) {
    phuong_tien** mang_moi = new phuong_tien*[suc_chua_moi];
    for (int i = 0; i < suc_chua_moi; ++i) {
        mang_moi[i] = nullptr;
    }
    for (int i = 0; i < so_luong_xe; ++i) {
        mang_moi[i] = danh_sach_xe[i];
    }
    delete[] danh_sach_xe;
    danh_sach_xe = mang_moi;
    suc_chua = suc_chua_moi;
}

bool bai_xe::them_xe(const phuong_tien& xe_moi) {
    if (so_luong_xe == suc_chua) {
        mo_rong_suc_chua(suc_chua * 2);
    }
    danh_sach_xe[so_luong_xe] = new phuong_tien(xe_moi);
    so_luong_xe++;
    return true;
}

bool bai_xe::xoa_xe(int ma_xe_can_xoa) {
    int vi_tri = -1;
    for (int i = 0; i < so_luong_xe; ++i) {
        if (danh_sach_xe[i]->lay_ma_xe() == ma_xe_can_xoa) {
            vi_tri = i;
            break;
        }
    }
    if (vi_tri == -1) return false;
    
    delete danh_sach_xe[vi_tri];
    for (int i = vi_tri; i < so_luong_xe - 1; ++i) {
        danh_sach_xe[i] = danh_sach_xe[i + 1];
    }
    danh_sach_xe[so_luong_xe - 1] = nullptr; 
    so_luong_xe--;
    return true;
}

bool bai_xe::chua_xe(int ma_xe_can_tim) const {
    for (int i = 0; i < so_luong_xe; ++i) {
        if (danh_sach_xe[i]->lay_ma_xe() == ma_xe_can_tim) return true;
    }
    return false;
}

void bai_xe::hien_thi_thong_tin() const {
    cout << "Bai " << ma_bai << " [" << kich_thuoc << "] "
         << so_luong_xe << "/" << suc_chua << " xe\n";
    for (int i = 0; i < so_luong_xe; ++i) {
        if(danh_sach_xe[i] != nullptr)
            danh_sach_xe[i]->hien_thi();
    }
}

class he_thong_quan_ly {
private:
    int suc_chua_he_thong;
    int so_luong_bai;
    bai_xe** danh_sach_bai;         

    int nhap_so_nguyen_hop_le();
    bool trung_ma_bai(int ma_kiem_tra) const;
    bool trung_ma_xe(int ma_kiem_tra) const;
    int sinh_ma_ngau_nhien() const;
    void mo_rong_he_thong(int suc_chua_moi);

public:
    he_thong_quan_ly();
    
    ~he_thong_quan_ly();
    he_thong_quan_ly(const he_thong_quan_ly& he_thong_khac);
    he_thong_quan_ly& operator=(const he_thong_quan_ly& he_thong_khac);
    
    void chay_menu();
};

he_thong_quan_ly::he_thong_quan_ly() : suc_chua_he_thong(5), so_luong_bai(0) {
    srand((unsigned)time(NULL));
    danh_sach_bai = new bai_xe*[suc_chua_he_thong];
    for(int i = 0; i < suc_chua_he_thong; ++i) {
        danh_sach_bai[i] = nullptr;
    }
}

he_thong_quan_ly::~he_thong_quan_ly() {
    for (int i = 0; i < so_luong_bai; ++i) {
        delete danh_sach_bai[i];
    }
    delete[] danh_sach_bai;
}

he_thong_quan_ly::he_thong_quan_ly(const he_thong_quan_ly& he_thong_khac) {
    suc_chua_he_thong = he_thong_khac.suc_chua_he_thong;
    so_luong_bai = he_thong_khac.so_luong_bai;
    danh_sach_bai = new bai_xe*[suc_chua_he_thong];
    for (int i = 0; i < suc_chua_he_thong; ++i) danh_sach_bai[i] = nullptr;
    for (int i = 0; i < so_luong_bai; ++i) {
        danh_sach_bai[i] = new bai_xe(*(he_thong_khac.danh_sach_bai[i]));
    }
}

he_thong_quan_ly& he_thong_quan_ly::operator=(const he_thong_quan_ly& he_thong_khac) {
    if (this != &he_thong_khac) {
        for (int i = 0; i < so_luong_bai; ++i) delete danh_sach_bai[i];
        delete[] danh_sach_bai;
        
        suc_chua_he_thong = he_thong_khac.suc_chua_he_thong;
        so_luong_bai = he_thong_khac.so_luong_bai;
        danh_sach_bai = new bai_xe*[suc_chua_he_thong];
        for (int i = 0; i < suc_chua_he_thong; ++i) danh_sach_bai[i] = nullptr;
        for (int i = 0; i < so_luong_bai; ++i) {
            danh_sach_bai[i] = new bai_xe(*(he_thong_khac.danh_sach_bai[i]));
        }
    }
    return *this;
}

void he_thong_quan_ly::mo_rong_he_thong(int suc_chua_moi) {
    bai_xe** mang_moi = new bai_xe*[suc_chua_moi];
    for (int i = 0; i < suc_chua_moi; ++i) mang_moi[i] = nullptr;
    for (int i = 0; i < so_luong_bai; ++i) {
        mang_moi[i] = danh_sach_bai[i];
    }
    delete[] danh_sach_bai;
    danh_sach_bai = mang_moi;
    suc_chua_he_thong = suc_chua_moi;
}

int he_thong_quan_ly::nhap_so_nguyen_hop_le() {
    int gia_tri;
    while (!(cin >> gia_tri)) {
        cout << "Loi kieu du lieu! Vui long nhap lai so nguyen: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return gia_tri;
}

bool he_thong_quan_ly::trung_ma_bai(int ma_kiem_tra) const {
    for (int i = 0; i < so_luong_bai; ++i) {
        if (danh_sach_bai[i]->lay_ma_bai() == ma_kiem_tra) return true;
    }
    return false;
}

bool he_thong_quan_ly::trung_ma_xe(int ma_kiem_tra) const {
    for (int i = 0; i < so_luong_bai; ++i) {
        if (danh_sach_bai[i]->chua_xe(ma_kiem_tra)) return true;
    }
    return false;
}

int he_thong_quan_ly::sinh_ma_ngau_nhien() const {
    return rand() % 9000 + 1000;
}

void he_thong_quan_ly::chay_menu() {
    int lua_chon;
    while (true) {
        cout << "\n===== QUAN LY BAI DO XE (GIAI DOAN 3 - CON TRO) =====\n";
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
        lua_chon = nhap_so_nguyen_hop_le();
        
        switch (lua_chon) {
        case 1: {
            if (so_luong_bai == suc_chua_he_thong) {
                mo_rong_he_thong(suc_chua_he_thong * 2);
                cout << "[He thong] Da tu dong mo rong suc chua he thong len " << suc_chua_he_thong << "!\n";
            }
            int ma_bai_nhap; char kich_thuoc_nhap;
            cout << "Ma bai: "; ma_bai_nhap = nhap_so_nguyen_hop_le();
            if (trung_ma_bai(ma_bai_nhap)) {
                cout << "Trung ma bai! ";
                ma_bai_nhap = sinh_ma_ngau_nhien();
                while (trung_ma_bai(ma_bai_nhap)) ma_bai_nhap = sinh_ma_ngau_nhien();
                cout << "Tu dong gan ma ngau nhien: " << ma_bai_nhap << "\n";
            }
            cout << "Kich thuoc (S/M/L): "; cin >> kich_thuoc_nhap;
            kich_thuoc_nhap = toupper(kich_thuoc_nhap);
            
            danh_sach_bai[so_luong_bai] = new bai_xe(ma_bai_nhap, kich_thuoc_nhap);
            so_luong_bai++;
            cout << "Da tao bai do " << ma_bai_nhap << "\n";
            break;
        }
        case 2: {
            if (so_luong_bai == 0) {
                cout << "Chua co bai do nao tren he thong!\n";
                break;
            }
            int ma_xe_nhap, gio_nhap, thoi_gian_nhap; 
            string loai_nhap;
            
            cout << "Ma xe: "; ma_xe_nhap = nhap_so_nguyen_hop_le();
            if (trung_ma_xe(ma_xe_nhap)) {
                cout << "Trung ma xe! ";
                ma_xe_nhap = sinh_ma_ngau_nhien();
                while (trung_ma_xe(ma_xe_nhap)) ma_xe_nhap = sinh_ma_ngau_nhien();
                cout << "Tu dong gan ma ngau nhien: " << ma_xe_nhap << "\n";
            }
            cout << "Loai (Car/Motorcycle/Bicycle): "; cin >> loai_nhap;
            cout << "Gio vao (0-23): "; gio_nhap = nhap_so_nguyen_hop_le();
            cout << "Thoi luong do (1-23): "; thoi_gian_nhap = nhap_so_nguyen_hop_le();
            
            phuong_tien xe_moi(ma_xe_nhap, loai_nhap, gio_nhap, thoi_gian_nhap);
            bool thanh_cong = false;
            
            // Tìm bãi ?? còn d? s?c ch?a
            for (int i = 0; i < so_luong_bai; ++i) {
                if (danh_sach_bai[i]->lay_so_luong_xe() < danh_sach_bai[i]->lay_suc_chua()) {
                    danh_sach_bai[i]->them_xe(xe_moi);
                    thanh_cong = true;
                    cout << "Da them xe " << ma_xe_nhap << " vao Bai " << danh_sach_bai[i]->lay_ma_bai() 
                         << " | Phi: $" << fixed << setprecision(2) << xe_moi.tinh_phi() << "\n";
                    break;
                }
            }
            
            // N?u các bãi ??u ??t gi?i h?n hi?n t?i, ép vào bãi ??u tiên ?? kích ho?t hàm mo_rong_suc_chua()
            if (!thanh_cong && so_luong_bai > 0) {
                danh_sach_bai[0]->them_xe(xe_moi);
                cout << "[He thong] Bai " << danh_sach_bai[0]->lay_ma_bai() << " da tu dong mo rong suc chua!\n";
                cout << "Da them xe " << ma_xe_nhap << " vao Bai " << danh_sach_bai[0]->lay_ma_bai() 
                     << " | Phi: $" << fixed << setprecision(2) << xe_moi.tinh_phi() << "\n";
            }
            break;
        }
        case 3: {
            int ma_bai_xoa;
            cout << "Ma bai can xoa: "; ma_bai_xoa = nhap_so_nguyen_hop_le();
            int vi_tri_tim_thay = -1;
            for (int i = 0; i < so_luong_bai; ++i) {
                if (danh_sach_bai[i]->lay_ma_bai() == ma_bai_xoa) {
                    vi_tri_tim_thay = i;
                    break;
                }
            }
            if (vi_tri_tim_thay != -1) {
                delete danh_sach_bai[vi_tri_tim_thay]; 
                for (int i = vi_tri_tim_thay; i < so_luong_bai - 1; ++i) {
                    danh_sach_bai[i] = danh_sach_bai[i + 1];
                }
                danh_sach_bai[so_luong_bai - 1] = nullptr; 
                so_luong_bai--;
                cout << "Da xoa bai do " << ma_bai_xoa << "\n";
            } else {
                cout << "Khong tim thay bai do!\n";
            }
            break;
        }
        case 4: {
            int ma_xe_xoa;
            cout << "Ma xe can lay ra: "; ma_xe_xoa = nhap_so_nguyen_hop_le();
            bool thanh_cong = false;
            for (int i = 0; i < so_luong_bai; ++i) {
                if (danh_sach_bai[i]->xoa_xe(ma_xe_xoa)) {
                    thanh_cong = true;
                    break;
                }
            }
            cout << (thanh_cong ? "Da lay xe ra (kem theo giai phong bo nho an toan)\n" : "Khong tim thay xe\n");
            break;
        }
        case 5: {
            if (so_luong_bai == 0) cout << "Khong co bai do nao.\n";
            for (int i = 0; i < so_luong_bai; ++i) {
                if(danh_sach_bai[i] != nullptr)
                    danh_sach_bai[i]->hien_thi_thong_tin();
            }
            break;
        }
        case 6: {
            int ma_bai_tim;
            cout << "Ma bai: "; ma_bai_tim = nhap_so_nguyen_hop_le();
            bool thanh_cong = false;
            for (int i = 0; i < so_luong_bai; ++i) {
                if (danh_sach_bai[i]->lay_ma_bai() == ma_bai_tim) {
                    danh_sach_bai[i]->hien_thi_thong_tin();
                    thanh_cong = true;
                    break;
                }
            }
            if (!thanh_cong) cout << "Khong tim thay bai do!\n";
            break;
        }
        case 7: {
            string loai_xe_tim;
            cout << "Loai xe (Car/Motorcycle/Bicycle): "; cin >> loai_xe_tim;
            bool co_xe = false;
            for (int i = 0; i < so_luong_bai; ++i) {
                bool da_in_ten_bai = false;
                for (int j = 0; j < danh_sach_bai[i]->lay_so_luong_xe(); ++j) {
                    if (danh_sach_bai[i]->lay_xe_tai(j)->lay_loai_xe() == loai_xe_tim) {
                        if (!da_in_ten_bai) {
                            cout << "-> Thuoc bai do " << danh_sach_bai[i]->lay_ma_bai() << "\n";
                            da_in_ten_bai = true;
                            co_xe = true;
                        }
                        danh_sach_bai[i]->lay_xe_tai(j)->hien_thi();
                    }
                }
            }
            if (!co_xe) cout << "Khong co xe loai nay!\n";
            break;
        }
        case 8: {
            string mang_loai_xe[3] = { "Car", "Motorcycle", "Bicycle" };
            for (int t = 0; t < 3; ++t) {
                int tong_so_xe = 0; 
                double tong_tien_phi = 0;
                for (int i = 0; i < so_luong_bai; ++i) {
                    for (int j = 0; j < danh_sach_bai[i]->lay_so_luong_xe(); ++j) {
                        if (danh_sach_bai[i]->lay_xe_tai(j)->lay_loai_xe() == mang_loai_xe[t]) {
                            tong_so_xe++;
                            tong_tien_phi += danh_sach_bai[i]->lay_xe_tai(j)->tinh_phi();
                        }
                    }
                }
                cout << mang_loai_xe[t] << ": ";
                if (tong_so_xe == 0) cout << "khong co xe\n";
                else cout << tong_so_xe << " xe | Trung Binh: $" << fixed << setprecision(2) << tong_tien_phi / tong_so_xe << "\n";
            }
            break;
        }
        case 9:
            return; // Tr? v? main(), Destructor c?a he_thong_quan_ly s? t? ??ng d?n d?p toàn b? vùng nh?
        default:
            cout << "Lua chon khong hop le!\n";
            break;
        }
    }
}

int main() {
    he_thong_quan_ly he_thong;
    he_thong.chay_menu();
    return 0;
}

