function filter_data = band_filter(data,p1,p2,s1,s2,fs)
wp = [p1 p2 ] / (fs/2);  %�q�a�I���W�v
ws = [s1 s2 ] / (fs/2);  %���a�I���W�v
alpha_p = 3; %�q�a���\�̤j�I�  db
alpha_s = 40;%���a���\�̤p�I�  db
%������ƩM�I���W�v
[ N3, wn ] = ellipord( wp , ws , alpha_p , alpha_s);  %��o�ಾ��ƨt��
[ b, a ] = ellip(N3,alpha_p,alpha_s,wn,'bandpass'); 
filter_data = filter(b,a,data);
