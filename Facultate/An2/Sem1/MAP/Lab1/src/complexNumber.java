public class complexNumber {

    int re;
    int im;

    public complexNumber(int re, int im){
        this.re = re;
        this.im = im;
    }

    public void add(complexNumber x){
        this.re = this.re + x.re;
        this.im = this.im + x.im;
    }

    public void sub(complexNumber x){
        this.re = this.re - x.re;
        this.im = this.im - x.im;
    }

    public void mul(complexNumber x){
        this.re = this.re * x.re - this.im * x.im;
        this.im = this.re * x.im + x.re * this.im;
    }

    public void div(complexNumber x){
        this.re = (this.re * x.re + this.im * this.im)/(x.re * x.re + x.im * x.im);
        this.im = (x.re * this.im - this.re * x.im)/(x.re * x.re + x.im * x.im);
    }

    public void inv(){
        this.im = - this.im;
    }

}

