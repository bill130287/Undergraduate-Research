function filter_data = band_filter(data,p1,p2,s1,s2,fs)
wp = [p1 p2 ] / (fs/2);  %通帶截止頻率
ws = [s1 s2 ] / (fs/2);  %阻帶截止頻率
alpha_p = 3; %通帶允許最大衰減為  db
alpha_s = 40;%阻帶允許最小衰減為  db
%獲取階數和截止頻率
[ N3, wn ] = ellipord( wp , ws , alpha_p , alpha_s);  %獲得轉移函數系數
[ b, a ] = ellip(N3,alpha_p,alpha_s,wn,'bandpass'); 
filter_data = filter(b,a,data);
