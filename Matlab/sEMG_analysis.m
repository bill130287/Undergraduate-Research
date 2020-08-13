clear all
close all
tic
format long
%%%read data%%%
action = {'用手推擋','技術犯規','兩次運球','拉人','非法用手','非法掩護','帶球走步','帶球撞人','推人或不帶球撞人','對手非法接觸'};
read_root = 'C:\Users\bill\Documents\MATLAB\Examples\matlab\DownloadWebContentRelatedtoaTermExample\';

read_fileL = 'left.txt';
read_fileR = 'right.txt';

k=1;
j=1;
L=1;

% %%% STFT value %%%%%%%%%%
window=hanning(100);    %
noverlap=60;            %
Nftt=1000;              %
FS=1000;                %
%%%%%%%%%%%%%%%%%%%%%%%%%%%

% %%% Band-pass filter value %%%%
fp1=20;                       %
fp2=498;                      %
fs1=50;                       %
fs2=490;                      %
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
tic
for i = 1 : 1
    read_folder = strcat('專題\',action{i},'\');
    data_l = textread(strcat(read_root,read_folder,read_fileL));
    data_r = textread(strcat(read_root,read_folder,read_fileR));
    data_l = data_l(1:end,1:end-1);
    data_r = data_r(1:end,1:end-1);
    
    [m,n] = size(data_l);
    data_EMG_L = zeros(4*(m/10),n);
    data_EMG_R = zeros(4*(m/10),n);
    unitv_ACC_L = zeros(3*(m/10),250);
    unitv_ACC_R = zeros(3*(m/10),250);
    unitv_Gyo_L = zeros(3*(m/10),250);
    unitv_Gyo_R = zeros(3*(m/10),250);
    
    data_l = data_l./1000-1.25;
    data_r = data_r./1000-1.25;
    %data_l=data_r./1.25;
    %data_r=data_r./1.25;
    k=1;
    j=1;
    L=1;
    for a = 1 : m/10
        data_EMG_L(j:j+3,:) = data_l(k:k+3,:);
        data_EMG_R(j:j+3,:) = data_r(k:k+3,:);
        unitv_ACC_L(L:L+2,:) = (data_l(k+4:k+6,1:250)./100)./(sqrt(sum(data_l(k+4:k+6,1:250).*data_l(k+4:k+6,1:250)+1e-8))/100);
        unitv_ACC_R(L:L+2,:) = (data_r(k+4:k+6,1:250)./100)./(sqrt(sum(data_r(k+4:k+6,1:250).*data_r(k+4:k+6,1:250)+1e-8))/100);
        unitv_Gyo_L(L:L+2,:) = (data_l(k+7:k+9,1:250)./100)./(sqrt(sum(data_l(k+7:k+9,1:250).*data_l(k+7:k+9,1:250)+1e-8))/100);
        unitv_Gyo_R(L:L+2,:) = (data_r(k+7:k+9,1:250)./100)./(sqrt(sum(data_r(k+7:k+9,1:250).*data_r(k+7:k+9,1:250)+1e-8))/100);
    
        k = k+10;
        j = j+4;
        L = L+3;
    end
    
    F_data_L = band_filter(data_EMG_L',fp1,fp2,fs1,fs2,FS);
    F_data_R = band_filter(data_EMG_R',fp1,fp2,fs1,fs2,FS);
    F_data_L = F_data_L';
    F_data_R = F_data_R';
    
    write_folder=strcat('test_1227\',action{i},'\EMG\');
    for a = 1 : 4
        output_L = [];
        output_R = [];
        for b = 0: m/10-1
            data_EMG_chL(b+1,:) = F_data_L(4*b+a,:);
            data_EMG_chR(b+1,:) = F_data_R(4*b+a,:);
            %Ndata_EMG_chL(j+1,:) = Ndata_EMG_L(4*j+a,:);
            %Ndata_EMG_chR(j+1,:) = Ndata_EMG_R(4*j+a,:);
        end
        for b = 1 : size(data_EMG_chL,1)
            [S,F,T] = spectrogram(data_EMG_chL(b,:),window,noverlap,Nftt,FS);
            S_log = 10*log10(abs(S));
            output_L = [output_L;S_log];
        end
        for b = 1 : size(data_EMG_chR,1)
            [S,F,T] = spectrogram(data_EMG_chR(b,:),window,noverlap,Nftt,FS);
            S_log = 10*log10(abs(S));
            output_R = [output_R;S_log];
        end
        
        write_fileL=sprintf('left_EMG_ch%d.csv',a);
        write_fileR=sprintf('right_EMG_ch%d.csv',a);
        %write_NfileL=sprintf('left_N_EMG_ch%d.csv',a);
        %write_NfileR=sprintf('right_N_EMG_ch%d.csv',a);
        dlmwrite(strcat(read_root,write_folder,write_fileL),output_L, 'precision', '%.4f')
        dlmwrite(strcat(read_root,write_folder,write_fileR),output_R, 'precision', '%.4f')
    end
    
    Acc_csv_L=reshape(unitv_ACC_L',750,m/10);
    Acc_csv_L=Acc_csv_L';
    Acc_csv_R=reshape(unitv_ACC_R',750,m/10);
    Acc_csv_R=Acc_csv_R';
    Gyo_csv_L=reshape(unitv_Gyo_L',750,m/10);
    Gyo_csv_L=Gyo_csv_L';
    Gyo_csv_R=reshape(unitv_Gyo_R',750,m/10);
    Gyo_csv_R=Gyo_csv_R';

    write_folder=strcat('test_1227\',action{i},'\');
    dlmwrite(strcat(read_root,write_folder,'ACC\','left_ACC.csv'),Acc_csv_L,'precision', '%.4f');
    dlmwrite(strcat(read_root,write_folder,'ACC\','right_ACC.csv'),Acc_csv_R, 'precision', '%.4f');
    dlmwrite(strcat(read_root,write_folder,'Gyo\','left_Gyo.csv'),Gyo_csv_L, 'precision', '%.4f');
    dlmwrite(strcat(read_root,write_folder,'Gyo\','right_Gyo.csv'),Gyo_csv_L, 'precision', '%.4f');
    
    
    
    clear all
    
end
toc