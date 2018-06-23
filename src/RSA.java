public class RSA {
    int RsaD;
    int RsaE;
    int RsaN;

    public RSA(){}

    //求解D
    public int qiuD(int e, int L){
        int D = 0;
        for(int i = 1; i < L; i++){
            if((e * i) % L == 1){
                D = i;
                break;
            }
        }
        return D;
    }

    //
    public int qiuL(int p, int q){
        int r;
        int N = p * q;
        if(p > q){
            int a = p;
            p = q;
            q = a;
        }
        if(q % p == 0){
            return q;
        }
        while (q % p != 0){
            r = q % p;
            q = p;
            p = r;
        }
        return N/p;
    }
    //加密
  public int RSAjiami(int s, int E, int N){
        int t = 1;
        while (E != 0){
            t = t * s;
            t = t % N;
            E--;
        }
        return t;
  }

    //解密
    public char RSAjiemi(int t, int D, int N){
        int m = 1;
        while(D != 0){
            m = m * t;
            m = m % N;
            D--;
        }
        char a = (char) m;
        return a;
    }



    public void Rsa(int p, int q, int e){
            int N = p * q;
            int L = (p - 1) * (q - 1);
            RsaD = qiuD(e, L);


    }
}
