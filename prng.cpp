#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <bitset>
#include <sstream>
#include <deque>
#include <cmath>

using namespace std;

deque<bool> binary(int x0, int num_bits) {
    bitset<sizeof(int) * 8> bits(x0);
    deque<bool> binary_digits;
    for (int i = num_bits - 1; i >= 0; --i) {
        binary_digits.push_back(bits[i]);
    }
    return binary_digits;
}

long long binToDec(string binStr)
{
    short i;
    long long res = 0;
    for (i = 0; i < sizeof(long long) * 8 && binStr[i]; ++i)
    {
        res <<= 1;
        res |= (binStr[i] - '0');
    }
    return res;
}

long long binDequeToDec(deque<bool> binStr)
{
    short i;
    long long res = 0;
    for (i = 0; i < sizeof(long long) * 8 && binStr[i]; ++i)
    {
        res <<= 1;
        res |= (binStr[i] - '0');
    }
    return res;
}

vector<int> splitStr(string str, char symbol)
{
    vector<int> elems;
    int elem;
    stringstream ss(str);
    while (ss >> elem) {
        elems.push_back(elem);
        if (ss.peek() == symbol) {
            ss.ignore();
        }
    }
    return elems;
}

pair<vector<int>, vector <deque <bool>>> splitStrFsr(string str, char symbol, string codeMethod)
{
    vector<int> elems;
    vector <deque <bool>> nfsrRegs;
    if (codeMethod == "lfsr") {
        char elem;
        int k = 0;
        vector<string> elemsLfsr(2);
        stringstream ss(str);
        while (ss >> elem) {
            elemsLfsr[k].push_back(elem);
            if (ss.peek() == symbol) {
                ss.ignore();
                k++;
            }
        }
        elems.push_back(stoi(elemsLfsr[1]));
        int elemsLfsrSize = elemsLfsr[0].size();
        for (int i = 0; i < elemsLfsrSize; i++)
        {
            if (elemsLfsr[0][i] == '1')
            {
                elems.push_back(elemsLfsrSize - 1 - i);
            }
        }
        //x0,coeffs
    }
    else {
        char elem;
        int k = 0;
        vector<string> elemsNfsr(3);
        stringstream ss(str);
        while (ss >> elem) {
            elemsNfsr[k].push_back(elem);
            if (ss.peek() == symbol) {
                ss.ignore();
                k++;
            }
        }
        for (int j = 0; j < elemsNfsr.size(); j++)
        {
            int elemsNfsrSize = elemsNfsr[j].size();
            int coeffsCount = 0;
            vector <int> elemsDop;
            for (int i = 0; i < elemsNfsrSize; i++)
            {
                if (elemsNfsr[j][i] == '1')
                {
                    elemsDop.push_back(elemsNfsrSize - 1 - i);
                    coeffsCount++;
                }
            }
            elems.push_back(coeffsCount);
            for (int i = 0; i < coeffsCount; i++)
            {
                elems.push_back(elemsDop[i]);
            }
        }
        //size1,coeffs1,size2,coeffs2,size3,coeffs3
        for (int i = 0; i < 3; i++)
        {
            deque<bool> strInDeq;
            for (int j = 0; j < elemsNfsr[i].size(); j++)
            {
                if (elemsNfsr[i][j] == '1')
                    strInDeq.push_back(1);
                else
                    strInDeq.push_back(0);
            }
            nfsrRegs.push_back(strInDeq);
        }
    }
    pair<vector<int>, vector <deque <bool>>> resPair = { elems , nfsrRegs };
    return resPair;
}

deque<bool> multRs(deque<bool> r1, deque<bool> r2) {
    int r1size = r1.size();
    int r2size = r2.size();
    if (r1size > r2size) {
        while (r2size != 0) {
            r1[r1size] &= r2[r2size];
            r2size--;
            r1size--;
        }
        return r1;
    }
    else {
        while (r1size != 0) {
            r1[r2size] &= r2[r1size];
            r2size--;
            r1size--;
        }
        return r2;
    }
    return r1;
}

deque<bool> orRs(deque<bool> r1, deque<bool> r2) {
    int r1size = r1.size();
    int r2size = r2.size();
    if (r1size > r2size) {
        while (r2size != 0) {
            r1[r1size] |= r2[r2size];
            r2size--;
            r1size--;
        }
        return r1;
    }
    else {
        while (r1size != 0) {
            r1[r2size] |= r2[r1size];
            r2size--;
            r1size--;
        }
        return r2;
    }
    return r1;
}

deque<bool> xorRs(deque<bool> r1, deque<bool> r2) {
    int r1size = r1.size();
    int r2size = r2.size();
    if (r1size > r2size) {
        while (r2size != 0) {
            r1[r1size] ^= r2[r2size];
            r2size--;
            r1size--;
        }
        return r1;
    }
    else {
        while (r1size != 0) {
            r1[r2size] ^= r2[r1size];
            r2size--;
            r1size--;
        }
        return r2;
    }
    return r1;
}

string findInStr(string const& str, int n) {
    if (str.length() < n) {
        return str;
    }
    return str.substr(0, n);
}

void dequePrint(deque<bool> reg) {
    cout << "deque: {";
    int regSize = reg.size();
    for (int i = 0; i < regSize; i++)
    {
        if (i != regSize - 1)
            cout << reg[i] << ",";
        else
            cout << reg[i] << "}";
    }
    cout << "; size: " << regSize << "." << endl;
    return;
}

int powmod(int x, int e, int n) {
    for (int i = 0; i < e - 1; i++)
    {
        x = (x * x) % n;
    }
    return x;
}


long long nod(long long x, long long y) {
    while (x != y) {
        if (x > y) {
            x = x - y;
        }
        else {
            y = y - x;
        }
    }
    return x;
}

bool mal_fermaPrime(long long p) {
    vector <long long> test;
    long long prime = 0;
    long long not_prime = 0;
    for (long long i = 1; i < 100; i++)
    {
        long long pi = p - i;
        if (pi >= 2 && nod(pi, p) == 1)
        {
            test.push_back(pi);
        }
    }
    for (long long i = 0; i < test.size(); i++)
    {
        long long a_step = test[i];
        long long a_step_dop = test[i];
        for (int j = 1; j < p - 1; j++)
        {
            a_step *= a_step_dop;
            a_step = a_step % p;
        }
        if (a_step == 1) {
            prime++;
        }
        else {
            not_prime++;
        }
    }
    if (prime <= not_prime)
        return false;
    else
        return true;
}

bool kratP(long long a, long long b) {
    for (int i = 2; i < b; i++)
    {
        if (b % i == 0 && a % i == 0 && mal_fermaPrime(i))
            return true;
    }
    return false;
}

vector<int> progressVector(int NumCount) {
    vector<int> shows;
    int NumCount10 = NumCount / 10;
    for (int i = 1; i < 10; i++)
    {
        shows.push_back(NumCount10 * i);
    }
    shows.push_back(NumCount - 1);
    cout << "\nThe process of generating pseudo-random numbers: \n\n";
    return shows;
}

deque <bool> gen_p_lc(int p) {
    deque <bool> ps;
    //Модуль, множитель, приращение, начальное значение
    long long m = 7875;
    long long a = 421;
    long long c = 1663;
    long long x0 = 32112;

    for (int i = 0; i < p; i++)
    {
        x0 = (x0 * a + c) % m;
        ps.push_back(x0 % 2);
    }
    return ps;
}


void helpFunc() {
    cout << "Введена команда c /h. Допустимые параметры:";
    cout << "\n\n/g:<код_метода> - параметр указывает на метод генерации ПСЧ, при этом код_метода может быть одним из следующих:\n";
    cout << "\n  lc – линейный конгруэнтный метод (Вход: модуль, множитель, приращение, начальное значение);\n  add – аддитивный метод (Вход: модуль, младший индекс, старший индекс, последовательность начальных значений);\n  5p – пятипараметрический метод (Вход: p, q1, q2, q3, w);\n  lfsr – регистр сдвига с обратной связью (РСЛОС) (Вход: двоичное представление вектора коэффициентов, начальное значение регистра);\n  nfsr – нелинейная комбинация РСЛОС (Вход: двоичное представление векторов коэффициентов для R1, R2, R3);\n  mt – вихрь Мерсенна (Вход: модуль, начальное значение x);\n  rc4 – RC4 (Вход: 256 начальных значений);\n  rsa – ГПСЧ на основе RSA (Вход: модуль n, число e, начальное значение x; e удовлетворяет условиям: 1 < e < (p-1)(q-1), НОД(e, (p-1)(q-1)) = 1, где p*q=n. x из интервала [1,n]);\n  bbs – алгоритм Блюма-Блюма-Шуба (Вход: Начальное значение x (взаимно простое с n));\n";
    cout << "\n\n/i:<число> - инициализационный вектор генератора.";
    cout << "\n\n/n:<длина> - количество генерируемых чисел. Если параметр не указан, - генерируется 10000 чисел.";
    cout << "\n\n/f:<полное_имя_файла> - полное имя файла, в который будут выводиться данные. Если параметр не указан, данные должны записываться в файл с именем rnd.dat.";
    cout << "\n\n/h – информация о допустимых параметрах командной строки программы.\n";
}

//Линейный конгруэнтный метод
void lcFunc(string codeMethod, vector <int> genVec, int NumCount, const char* fileName, bool defaultVec) {
    long long m = 12960;
    long long a = 1741;
    long long c = 2731;
    long long x0 = 1;
    if (!defaultVec) {
        m = genVec[0];
        a = genVec[1];
        c = genVec[2];
        x0 = genVec[3];
    }
    if (m <= 0 || a > m || a < 0 || c > m || c < 0 || x0 > m || x0 < 0) {
        cout << "\nОшибка. Параметры не соответствуют требованиям.\n";
        return;
    }
    if (nod(c, m) != 1) {
        cout << "\nПараметры не соответствуют требованиям теоремы 3.1 (Пункт 1).\n";
    }
    if (!(kratP(a - 1, m))) {
        cout << "\nПараметры не соответствуют требованиям теоремы 3.1 (Пункт 2).\n";
    }
    if (m % 4 == 0 && (a - 1) % 4 != 0) {
        cout << "\nПараметры не соответствуют требованиям теоремы 3.1 (Пункт 3).\n";
    }
    vector<int> showsVector = progressVector(NumCount);
    int check_progress_index = 0;

    ofstream f;
    f.open(fileName, ios::out);
    for (int i = 0; i < NumCount; i++)
    {
        x0 = (x0 * a + c) % m;
        if (defaultVec)
            f << x0 % 1001 << ",";
        else
            f << x0 << ",";

        if (i == showsVector[check_progress_index]) {
            cout << (check_progress_index + 1) * 10 << "% completed\n";
            check_progress_index++;
        }
    }
    f.close();
    return;
}

//Аддитивный ГСПЧ
void addFunc(string codeMethod, vector <int> genVec, int NumCount, const char* fileName, bool defaultVec) {
    //Вход: модуль, младший индекс, старший индекс, последовательность начальных значений
    long long m = 8001;
    long long k = 18;
    long long j = 65;
    long long x0;
    vector <long long> xNs;
    if (!defaultVec) {
        m = genVec[0];
        k = genVec[1];
        j = genVec[2];
        for (int i = 3; i < genVec.size(); i++)
        {
            xNs.push_back(genVec[i]);
        }
    }
    else {
        xNs = { 816,159,798,290,168,441,691,655,874,220,125,977,586,381,868,294,948,437,581,181,701,536,11,672,103,601,794,189,12,130,386,828,288,183,117,456,624,807,110,498,27,234,474,613,615,341,906,562,778,486,155,276,894,441,226,762,234,762,98,458,399,445,765,223,879 };
    }

    if (k < 1 || k >= j || j < 1) {
        cout << "\nОшибка. Параметры не соответствуют требованиям.\n";
        return;
    }

    vector<int> showsVector = progressVector(NumCount);
    int check_progress_index = 0;

    ofstream f;
    f.open(fileName, ios::out);
    long long maxkj = max(k, j);
    if (xNs.size() < maxkj) {
        cout << "\nОшибка. Параметры не соответствуют требованиям (Переданных начальных значений не хватает).\n";
        return;
    }
    for (int i = maxkj + 1; i < NumCount + maxkj + 1; i++)
    {
        x0 = (xNs[i - k] + xNs[i - j]) % m;
        xNs.push_back(x0);
        if (defaultVec)
            f << x0 % 1001 << ",";
        else
            f << x0 << ",";

        if (i == showsVector[check_progress_index]) {
            cout << (check_progress_index + 1) * 10 << "% completed\n";
            check_progress_index++;
        }
    }
    f.close();
    return;
}

//Пятипараметрический метод
void fivePFunc(string codeMethod, vector <int> genVec, int NumCount, const char* fileName, bool defaultVec) {
    //Вход: p, q1, q2, q3, w
    int p = 4253;
    long long q1 = 1093;
    long long q2 = 2254;
    long long q3 = 3297;
    int w = 16;
    if (!defaultVec) {
        p = genVec[0];
        q1 = genVec[1];
        q2 = genVec[2];
        q3 = genVec[3];
        w = genVec[4];
    }

    if (q1 >= p || q2 >= p || q3 >= p) {
        cout << "\nОшибка. Параметры не соответствуют требованиям.\n";
        return;
    }

    int regLength = p;
    deque <bool> reg = gen_p_lc(p);
    vector<int> showsVector = progressVector(NumCount);
    int check_progress_index = 0;

    ofstream f;
    f.open(fileName, ios::out);
    for (int i = 0; i < NumCount; i++)
    {
        bool xNplusP = reg[regLength - q1 - 1] ^ reg[regLength - q2 - 1] ^ reg[regLength - q3 - 1];
        reg.push_front(xNplusP);
        reg.pop_back();
        long long ReginDec = 0;
        for (int h = 0; h < w; h++)
        {
            ReginDec *= 2;
            ReginDec += reg[h];
        }
        if (defaultVec)
            f << ReginDec % 1001 << ",";
        else
            f << ReginDec << ",";

        if (i == showsVector[check_progress_index]) {
            cout << (check_progress_index + 1) * 10 << "% completed\n";
            check_progress_index++;
        }
    }
    f.close();
    return;
}

//РСЛОС
void lfsrFunc(string codeMethod, vector <int> genVec, int NumCount, const char* fileName, bool defaultVec) {
    //Вход: двоичное представление вектора коэффициентов, начальное значение регистра
    if (defaultVec) {
        genVec = { 121, 14, 5, 3, 1, 0 }; // x0, coeffs (100000000101011)
    }
    int x0 = genVec[0];
    int x0Length = log2(x0) + 1;
    int regLength = x0Length - 1;
    bool bigCoeff = false;
    for (int i = 1; i < genVec.size(); i++)
    {
        if (genVec[i] > regLength) {
            regLength = genVec[i] + 1;
            bigCoeff = true;
        }
    }
    if (x0 < 0) {
        cout << "\nОшибка. Параметры не соответствуют требованиям.\n";
        return;
    }

    vector<int> showsVector = progressVector(NumCount);
    int check_progress_index = 0;

    deque<bool> reg;
    if (!bigCoeff) {
        regLength++;
        reg = binary(x0, regLength);
    }
    else {
        reg.assign(regLength - x0Length, 0);
        deque<bool> regDop = binary(x0, x0Length);
        for (int i = 0; i < regDop.size(); i++)
        {
            reg.push_back(regDop[i]);
        }
    }
    ofstream f;
    f.open(fileName, ios::out);
    for (int i = 0; i < NumCount; i++)
    {
        bool xNplusP = reg[regLength - genVec[1] - 1];
        for (int j = 2; j < genVec.size(); j++)
        {
            xNplusP ^= reg[regLength - genVec[j] - 1];
        }
        reg.push_front(xNplusP);
        reg.pop_back();
        long long ReginDec = 0;
        for (int h = 0; h < reg.size(); h++)
        {
            ReginDec *= 2;
            ReginDec += reg[h];
        }
        if (defaultVec)
            f << ReginDec % 1001 << ",";
        else
            f << ReginDec << ",";

        if (i == showsVector[check_progress_index]) {
            cout << (check_progress_index + 1) * 10 << "% completed\n";
            check_progress_index++;
        }
    }
    f.close();
    return;
}

// нелинейная комбинация РСЛОС
void nfsrFunc(string codeMethod, vector <int> genVec, int NumCount, const char* fileName, vector <deque <bool>> nfsrRegs, bool defaultVec) {
    //Вход: двоичное представление векторов коэффициентов для R1, R2, R3
    if (defaultVec) {
        genVec = { 5, 14, 4, 3, 1, 0, 3, 15, 1, 0, 5, 16, 5, 3, 2, 0 }; // size1,coeffs1,size2,coeffs2,size3,coeffs3 (100000000011011,1000000000000011,10000000000101101)
        nfsrRegs = { {1,0,0,0,0,0,0,0,0,0,1,1,0,1,1}, {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1}, {1,0,0,0,0,0,0,0,0,0,0,1,0,1,1,0,1} };
    }
    int nachR1 = 1;
    int endR1 = genVec[0] + 1;
    int nachR2 = endR1 + 1;
    int endR2 = genVec[endR1] + nachR2 + 1;
    int nachR3 = endR2 + 1;
    int endR3 = genVec.size();
    vector<int> startsRslos = { nachR1, nachR2, nachR3 };
    vector<int> endssRslos = { endR1, endR2, endR3 };
    vector<int> regLengths;
    for (int i = 0; i < 3; i++)
    {
        regLengths.push_back(nfsrRegs[i].size());
    }
    vector <deque<bool>> regs = nfsrRegs;

    vector<int> showsVector = progressVector(NumCount);
    int check_progress_index = 0;

    ofstream f;
    f.open(fileName, ios::out);
    for (int i = 0; i < NumCount; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            int startH = startsRslos[j];
            int endH = endssRslos[j];
            bool xNext = regs[j][regLengths[j] - genVec[startH] - 1];
            for (int h = startH; h < endH; h++)
            {
                xNext ^= regs[j][regLengths[j] - genVec[h] - 1];
            }
            regs[j].push_front(xNext);
            regs[j].pop_back();
        }
        vector <deque<bool>> regs2(2);
        regs2[0] = multRs(regs[0], regs[1]);
        regs2[1] = multRs(regs[1], regs[2]);
        deque<bool> resR = xorRs(xorRs(regs2[0], regs2[1]), regs[2]);

        long long ReginDec = 0;
        for (int h = 0; h < resR.size(); h++)
        {
            ReginDec *= 2;
            ReginDec += resR[h];
        }
        if (defaultVec)
            f << ReginDec % 1001 << ",";
        else
            f << ReginDec << ",";

        if (i == showsVector[check_progress_index]) {
            cout << (check_progress_index + 1) * 10 << "% completed\n";
            check_progress_index++;
        }
    }
    f.close();
    return;
}

//Вихрь Мерсенна
void mtFunc(string codeMethod, vector <int> genVec, int NumCount, const char* fileName, bool defaultVec) {
    //Вход: модуль, начальное значение x
    int p = 624;
    int w = 32;
    //string uBin = "10000000000000000000000000000000";
    //string hBin = "01111111111111111111111111111111";
    long long uDec = 2147483647;
    long long hDec = 2147483648;
    long long r = 31;
    long long q = 397;
    long long a = 2567483615;
    long long u = 11;
    long long s = 7;
    long long t = 15;
    long long l = 18;
    long long b = 2636928640;
    long long c = 4022730752;
    if (defaultVec) {
        genVec = { 10001, 8191 };
    }
    long long zMod = genVec[0];
    long long x0 = genVec[1];
    vector <long long> x_zns(1, x0);
    for (int i = 0; i < p; i++)
    {
        x_zns.push_back(abs(1812433253 * (x_zns[i - 1] ^ (x_zns[i - 1] >> 30)) + i));
    }

    vector<int> showsVector = progressVector(NumCount);
    int check_progress_index = 0;

    ofstream f;
    f.open(fileName, ios::out);
    int n = 0;
    for (int countN = 0; countN < NumCount; countN++)
    {
        long long xn = x_zns[n];
        long long xnPlus1 = x_zns[(n + 1) % p];
        long long yNew = (xn & uDec) | (xnPlus1 & hDec);
        int yNewLength = log2(yNew) + 1;
        deque<bool> yBin = binary(yNew, yNewLength);
        long long Xnew;
        yNew >>= 1;
        long long xnqp = x_zns[(n + q) % p];
        if (yBin[yBin.size() - 1] == 1)
            Xnew = xnqp ^ yNew ^ a;
        else
            Xnew = xnqp ^ yNew ^ 0;
        yNew = Xnew;
        yNew = yNew ^ (yNew >> u);
        yNew = yNew ^ ((yNew << s) & b);
        yNew = yNew ^ ((yNew << t) & c);
        long long zNew = yNew ^ (yNew >> l);
        if (defaultVec)
            f << (zNew % zMod) % 1001 << ",";
        else
            f << zNew % zMod << ",";

        if (countN == showsVector[check_progress_index]) {
            cout << (check_progress_index + 1) * 10 << "% completed\n";
            check_progress_index++;
        }
        x_zns[n] = Xnew;
        n = (n + 1) % p;
    }
    f.close();
    return;
}

//RC4
void rc4Func(string codeMethod, vector <int> genVec, int NumCount, const char* fileName, bool defaultVec) {
    //Вход: 256 начальных значений
    if (defaultVec) {
        genVec = { 802,720,341,337,961,882,417,785,198,727,899,372,374,425,556,615,813,768,840,183,893,568,73,387,18,436,182,125,806,899,485,607,619,825,944,579,707,360,363,904,87,262,276,460,687,831,75,499,599,915,681,492,483,754,878,500,189,60,624,994,959,109,600,577,934,544,156,640,903,519,544,990,781,819,449,468,650,524,967,248,438,647,739,920,400,617,419,588,676,43,581,634,151,181,211,84,724,367,723,627,886,267,617,667,85,65,134,735,589,100,983,26,747,721,945,147,337,364,734,13,406,315,647,556,496,858,640,220,224,362,847,110,629,463,776,713,528,909,448,116,9,430,141,755,151,86,901,488,449,635,500,855,950,147,410,446,4,49,665,227,411,511,336,39,974,112,752,501,21,200,617,29,629,757,784,779,843,684,266,292,319,766,146,269,912,556,714,916,605,378,142,15,889,478,54,862,590,806,363,610,5,979,638,634,736,421,413,578,105,679,869,424,444,14,692,356,569,405,271,173,783,413,188,671,891,242,533,480,48,895,89,53,873,727,686,608,147,98,185,252,776,54,675,220,67,366,576,636,771,846,808,553,259,996,224,149 };
    }
    vector <int> k = genVec;
    vector <int> s = genVec;
    int j = 0;
    for (int i = 0; i < 256; i++)
    {
        j = (j + s[i] + k[i]) % 256;
        swap(s[i], s[j]);
    }
    int i = 0;
    j = 0;

    vector<int> showsVector = progressVector(NumCount);
    int check_progress_index = 0;

    ofstream f;
    f.open(fileName, ios::out);
    for (int countN = 0; countN < NumCount; countN++)
    {
        i = (i + 1) % 256;
        j = (j + s[j]) % 256;
        swap(s[i], s[j]);
        int t = (s[i] + s[j]) % 256;
        if (defaultVec)
            f << s[t] % 1001 << ",";
        else
            f << s[t] << ",";

        if (countN == showsVector[check_progress_index]) {
            cout << (check_progress_index + 1) * 10 << "% completed\n";
            check_progress_index++;
        }
    }
    f.close();
    return;
}

//ГПСЧ на основе RSA
void rsaFunc(string codeMethod, vector <int> genVec, int NumCount, const char* fileName, bool defaultVec) {
    //Вход: модуль n, число e, начальное значение x; e удовлетворяет условиям: 1 < e < (p-1)(q-1), НОД(e, (p-1)(q-1)) = 1, где p*q=n. x из интервала [1,n]
    if (defaultVec) {
        genVec = { 7191817, 151, 69 };
    }
    int n = genVec[0];
    int e = genVec[1];
    int x = genVec[2];
    int l = 20;

    if (e <= 1 || x < 1 || x > n - 1) {
        cout << "\nОшибка. Параметры не соответствуют требованиям.\n";
        return;
    }

    vector<int> showsVector = progressVector(NumCount);
    int check_progress_index = 0;

    ofstream f;
    f.open(fileName, ios::out);
    for (int countN = 0; countN < NumCount; countN++)
    {
        string zs = "";
        for (int i = 0; i < l; i++)
        {
            x = powmod(x, e, n);
            char z = '0';
            if (x % 2 != 0)
                z = '1';
            zs.push_back(z);
        }
        if (defaultVec)
            f << binToDec(zs) % 1001 << ",";
        else
            f << binToDec(zs) << ",";

        if (countN == showsVector[check_progress_index]) {
            cout << (check_progress_index + 1) * 10 << "% completed\n";
            check_progress_index++;
        }
    }
    f.close();
    return;
}

//Алгоритм Блюма-Блюма-Шуба
void bbsFunc(string codeMethod, vector <int> genVec, int NumCount, const char* fileName, bool defaultVec) {
    //Вход: Начальное значение x (взаимно простое с n)
    if (defaultVec) {
        genVec = { 8627 };
    }
    int x0 = genVec[0];
    int n = 16637;
    int l = 10;

    if (nod(x0, n) != 1) {
        cout << "\nПараметры не соответствуют требованиям (x и n не взаимно простые).\n";
    }

    vector<int> showsVector = progressVector(NumCount);
    int check_progress_index = 0;

    ofstream f;
    f.open(fileName, ios::out);
    for (int countN = 0; countN < NumCount; countN++)
    {
        x0 = (x0 * x0) % n;
        string zs = "";
        for (int i = 0; i < l; i++)
        {
            x0 = (x0 * x0) % n;
            char z = '0';
            if (x0 % 2 != 0)
                z = '1';
            zs.push_back(z);
        }
        if (defaultVec)
            f << binToDec(zs) % 1001 << ",";
        else
            f << binToDec(zs) << ",";

        if (countN == showsVector[check_progress_index]) {
            cout << (check_progress_index + 1) * 10 << "% completed\n";
            check_progress_index++;
        }
    }
    f.close();
    return;
}

void setMethod(string codeMethod, vector <int> genVec, int NumCount, const char* fileName, int genVecSize, vector <deque <bool>> nfsrRegs, bool defaultVec) {
    if (codeMethod == "lc")
        lcFunc(codeMethod, genVec, NumCount, fileName, defaultVec);
    else if (codeMethod == "add")
        addFunc(codeMethod, genVec, NumCount, fileName, defaultVec);
    else if (codeMethod == "5p")
        fivePFunc(codeMethod, genVec, NumCount, fileName, defaultVec);
    else if (codeMethod == "lfsr")
        lfsrFunc(codeMethod, genVec, NumCount, fileName, defaultVec);
    else if (codeMethod == "nfsr")
        nfsrFunc(codeMethod, genVec, NumCount, fileName, nfsrRegs, defaultVec);
    else if (codeMethod == "mt")
        mtFunc(codeMethod, genVec, NumCount, fileName, defaultVec);
    else if (codeMethod == "rc4")
        rc4Func(codeMethod, genVec, NumCount, fileName, defaultVec);
    else if (codeMethod == "rsa")
        rsaFunc(codeMethod, genVec, NumCount, fileName, defaultVec);
    else if (codeMethod == "bbs")
        bbsFunc(codeMethod, genVec, NumCount, fileName, defaultVec);
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "Rus");
    string codeMethod;
    vector <int> genVec;
    vector <deque <bool>> nfsrRegs;
    int NumCount = 10000;
    string fName = "rnd.dat";
    bool defaultVec = true;
    for (int i = 0; argv[i]; i++)
    {
        string checkStr = string(argv[i]);
        if (findInStr(checkStr, 2) == "/h") {
            helpFunc();
            return 0;
        }
        if (checkStr.length() > 2) {
            string ifStr = findInStr(checkStr, 3);
            string subStr = checkStr.substr(3, checkStr.length());
            if (ifStr == "/g:") {
                codeMethod = subStr;
            }
            if (ifStr == "/i:" && (codeMethod == "lfsr" || codeMethod == "nfsr")) {
                char symbol = ',';
                pair<vector<int>, vector <deque <bool>>> nfsrPair;
                nfsrPair = splitStrFsr(subStr, symbol, codeMethod);
                genVec = nfsrPair.first;
                nfsrRegs = nfsrPair.second;
                defaultVec = false;
            }
            else if (ifStr == "/i:") {
                char symbol = ',';
                genVec = splitStr(subStr, symbol);
                defaultVec = false;
            }
            if (ifStr == "/n:") {
                NumCount = stoi(subStr);
            }
            if (ifStr == "/f:") {
                fName = subStr;
            }
        }
    }
    const char* fileName = fName.c_str();
    int genVecSize = genVec.size();
    setMethod(codeMethod, genVec, NumCount, fileName, genVecSize, nfsrRegs, defaultVec);
    cout << "\nGeneration method: " << codeMethod << endl;
    cout << "Count of generated numbers: " << NumCount << endl;
    cout << "Full name of the output file: " << fileName << endl;
    return 0;
}