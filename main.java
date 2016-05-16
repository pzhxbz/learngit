package com.example.pzhxbz.note;

import android.app.AlertDialog;
import android.content.ContentValues;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.database.Cursor;
import android.database.SQLException;
import android.database.sqlite.SQLiteDatabase;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.ContextMenu;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.animation.AlphaAnimation;
import android.view.animation.Animation;
import android.view.animation.AnimationSet;
import android.view.animation.RotateAnimation;
import android.view.animation.ScaleAnimation;
import android.widget.AbsListView;
import android.widget.AdapterView;
import android.widget.BaseAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.ListView;
import android.widget.SimpleAdapter;
import android.widget.TextView;
import android.widget.Toast;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.Statement;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;

public class MainActivity extends AppCompatActivity {
    private ImageButton add;
    private Button save;
    private EditText title;
    private EditText content;
    ListView list;
    SQLiteDatabase mDb;
    SQLiteDatabaseDao dao;
    String strTitle;
    String strContent;
    public ArrayList<HashMap<String, Object>> listData;
    MyAdapter listItemAdapter;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        dao =new SQLiteDatabaseDao();
        list = (ListView)findViewById(R.id.list_item);
        listItemAdapter = new MyAdapter(this);
        list.setAdapter(listItemAdapter);
        list.setOnItemClickListener(listviewLongPress);
        list.setOnScrollListener(listScroll);
        setupViewComponent();
    }
    private void setupViewComponent(){
        add=(ImageButton)findViewById(R.id.add);
        add.setOnClickListener(addOnClick);
    }
    private ListView.OnScrollListener listScroll=new ListView.OnScrollListener(){
        private boolean scrollFlag = false;// 标记是否滑动
        private int lastVisibleItemPosition;// 标记上次滑动位置
        @Override
        public void onScrollStateChanged(AbsListView view, int scrollState) {
// TODO Auto-generated method stub
            if (scrollState == AbsListView.OnScrollListener.SCROLL_STATE_TOUCH_SCROLL) {
                scrollFlag = true;
            } else {
                scrollFlag = false;
            }
        }
        @Override
        public void onScroll(AbsListView view, int firstVisibleItem, int visibleItemCount, int totalItemCount) {
            AnimationSet animationSet = new AnimationSet(true);
            if (scrollFlag) {
                if (firstVisibleItem < lastVisibleItemPosition) {
                    AlphaAnimation alphaAnimation = new AlphaAnimation(0,1);
                    alphaAnimation.setDuration(500);
                    animationSet.addAnimation(alphaAnimation);
                    alphaAnimation.setFillAfter(true);
                    add.startAnimation(alphaAnimation);
                }
                if (firstVisibleItem > lastVisibleItemPosition) {
                    AlphaAnimation alphaAnimation = new AlphaAnimation(1, 0);
                    alphaAnimation.setDuration(500);
                    animationSet.addAnimation(alphaAnimation);
                    alphaAnimation.setFillAfter(true);
                    add.startAnimation(alphaAnimation);
                }
                if (firstVisibleItem == lastVisibleItemPosition) {
                    return;
                }
                lastVisibleItemPosition = firstVisibleItem;
            }
        }
    };
    private Button.OnClickListener addOnClick=new Button.OnClickListener(){
        public void onClick(View v){
            AnimationSet animationSet = new AnimationSet(true);
            RotateAnimation rotateAnimation = new RotateAnimation(0,360+45,
                    Animation.RELATIVE_TO_SELF,0.5f,
                    Animation.RELATIVE_TO_SELF,0.5f);
            rotateAnimation.setDuration(750);
            animationSet.addAnimation(rotateAnimation);
            add.startAnimation(animationSet);
            animationSet.setAnimationListener(new Animation.AnimationListener() {
                @Override
                public void onAnimationStart(Animation animation) {
                }
                @Override
                public void onAnimationRepeat(Animation animation) {
                }
                @Override
                public void onAnimationEnd(Animation animation) {
                    setContentView(R.layout.edit);
                    save = (Button) findViewById(R.id.save);
                    save.setOnClickListener(saveOnClick);
                }
            });
        }
    };
    private Button.OnClickListener saveOnClick=new Button.OnClickListener(){
        @Override
        public void onClick(View v) {
            title=(EditText)findViewById(R.id.edtitle);
            content=(EditText)findViewById(R.id.note);
            strTitle=title.getText().toString();
            strContent=content.getText().toString();
            if(!strContent.isEmpty()&&!strContent.isEmpty())
            {
                dao.insert(mDb, "note", strTitle, strContent);
            }
            else{
                AlertDialog.Builder info=new AlertDialog.Builder(MainActivity.this);
                info.setTitle("warning");
                info.setMessage("你好像少填了一点东西吧,我是不会保存的");
                info.setPositiveButton("确定", null);
                info.show();
                return;
            }
            setContentView(R.layout.activity_main);
            add=(ImageButton)findViewById(R.id.add);
            add.setOnClickListener(addOnClick);
            ListView list = (ListView)findViewById(R.id.list_item);
            dao.getAllData("note");
            listItemAdapter = new MyAdapter(MainActivity.this );
            list.setAdapter(listItemAdapter);
            list.setOnScrollListener(listScroll);
            list.setOnItemClickListener(listviewLongPress);
        }
    };

    ListView.OnItemClickListener listviewLongPress = new ListView.OnItemClickListener() {
        @Override
        public void onItemClick(AdapterView<?> arg0, View v,
                                final int position,long id) {
            // TODO Auto-generated method stub
            HashMap<String, Object> map = listData
                    .get(position);
            int pos = Integer.valueOf((map.get("id")
                    .toString()));
            String title=map.get("title").toString();
            String content=map.get("content").toString();
            if (dao.delete(mDb, "note", pos)) {
                listData.remove(position);
                listItemAdapter.notifyDataSetChanged();
            }
            setContentView(R.layout.edit);
            save=(Button)findViewById(R.id.save);
            save.setOnClickListener(saveOnClick);
            EditText editTitle=(EditText)findViewById(R.id.edtitle);
            EditText editContent=(EditText)findViewById(R.id.note);
            editTitle.setText(title);
            editContent.setText(content);
                                }
                           // }).show();
       // }
    };
    @Override
    public void finish() {
        // TODO Auto-generated method stub
        super.finish();
        mDb.close();
    }
    public String time(){
        Date date=new Date();
        DateFormat format=new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        String time=format.format(date);
        return time;
    }
    class SQLiteDatabaseDao {

        public SQLiteDatabaseDao() {
            mDb = openOrCreateDatabase("users.db",
                    SQLiteDatabase.CREATE_IF_NECESSARY, null);
            createTable(mDb, "note");
            getAllData("note");
        }
        public void createTable(SQLiteDatabase mDb, String table) {
            try {
                mDb.execSQL("create table if not exists "
                        + table
                        + " (id integer primary key autoincrement, "
                        + "title text not null, content text not null,date text not null);");
            } catch (SQLException e) {
                Toast.makeText(getApplicationContext(), "数据表创建失败",
                        Toast.LENGTH_LONG).show();
            }
        }
        public void insert(SQLiteDatabase mDb, String table,String s1,String s2) {
            ContentValues values = new ContentValues();
            values.put("title", s1);
            values.put("content", s2);
            values.put("date", time());
            mDb.insert(table, null, values);
        }
        public void getAllData(String table) {
            Cursor c = mDb.rawQuery("select * from note", null);
            listData = new ArrayList<HashMap<String, Object>>();
            while (c.moveToNext()) {
                HashMap<String, Object> map = new HashMap<String, Object>();
                    map.put("id", c.getString(0));
                    map.put("title", c.getString(1));
                    map.put("content", c.getString(2));
                    map.put("date", c.getString(3));
                    listData.add(map);
            }
        }
        public boolean delete(SQLiteDatabase mDb, String table, int id) {
            String whereClause = "id=?";
            String[] whereArgs = new String[] { String.valueOf(id) };
            try {
                mDb.delete(table, whereClause, whereArgs);
            } catch (SQLException e) {
                Toast.makeText(getApplicationContext(), "删除数据库失败",
                        Toast.LENGTH_LONG).show();
                return false;
            }
            return true;
        }
    }
    class MyAdapter extends BaseAdapter {
        private LayoutInflater mInflater;
        public MyAdapter(Context context) {
            this.mInflater = LayoutInflater.from(context);
        }
        @Override
        public Object getItem(int position) {
            return null;
        }
        @Override
        public int getCount() {
            return listData.size();
        }
        @Override
        public long getItemId(int position) {
            return 0;
        }
        @Override
        public View getView(final int position, View convertView, ViewGroup parent) {
            ViewHolder holder;
                View myView = mInflater.inflate(R.layout.item, null);
                holder = new ViewHolder();
                dao.getAllData("note");
                holder.title = (TextView) myView.findViewById(R.id.title);
                holder.title.setText(listData.get(position).get("title").toString());
                holder.text = (TextView) myView.findViewById(R.id.content);
                holder.text.setText(listData.get(position).get("content").toString());
                holder.bt = (ImageButton) myView.findViewById(R.id.delete);
                holder.date = (TextView) myView.findViewById(R.id.date);
                holder.date.setText(listData.get(position).get("date").toString());
            final int arg = position;
            holder.bt.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View v) {
                    AlertDialog.Builder info=new AlertDialog.Builder(MainActivity.this);
                    //info.setTitle("  ");
                    info.setMessage("是否删除");
                    info.setNegativeButton("确定", new DialogInterface.OnClickListener() {
                        public void onClick(
                                DialogInterface dialoginterface, int i) {
                            //int mListPos = info.position;
                            HashMap<String, Object> map = listData
                                    .get(position);
                            int id = Integer.valueOf((map.get("id")
                                    .toString()));
                            if (dao.delete(mDb, "note", id)) {
                                listData.remove(position);
                                listItemAdapter.notifyDataSetChanged();
                            }
                        }
                    });
                    info.setPositiveButton("取消", null);
                    info.show();
                }
            });
            return myView;
        }
        public final class ViewHolder {
            public TextView title;
            public TextView text;
            public ImageButton bt;
            public TextView date;
        }
    }
}

