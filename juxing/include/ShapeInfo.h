#ifndef SHAPEINFO_H
#define SHAPEINFO_H
class ShapeInfo
{
    public:
        ShapeInfo();
        virtual ~ShapeInfo();
        void print(int a,int x1,int y1,int x2,int y2);
        void print();
        void draw();
        void draw_change();
        int load(int a);
        bool is_in(int x,int y);
        void trans(int change_x,int change_y);
        void add_change();
        //void to(int change_x,int change_y);
    protected:
    private:
        int info=-1;
        int x1,y1;
        int x2,y2;
        int id;
        int change_x1=0,change_y1=0;
};

#endif // SHAPEINFO_H
