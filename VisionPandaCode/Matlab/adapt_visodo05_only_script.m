 clear

% % robot_output = input('Which robot output file to process?\n','s')
% % data = load(robot_output);

data = load('adaptive_visodo\nats_lab_data\live_runs\model_output.mat');

%marker positions
M=[0 0;137.5 -78; 79 -200.5; 503.5 46];

time = data.output(2,:);
tfinal = length(time);
% % for t=1:tfinal
% %     if time(t)==0
% %         ti=t+1;
% %     end
% % end
% % ti=ti-1; % start at time=0;
% % ti=4;
ft(1) = 0;%time(ti)-time(ti-1);
time = data.output(2,:);
num_ipts = data.output(3,:);
hist_ind = data.output(4,:);
filter = data.output(5,:);
matches = data.output(6,:);
miss = data.output(7,:);

ff_disp = data.output(14:17,:);
cum_disp = data.output(18:21,:);
Sigma = data.output(22,:);
Nu = data.output(23,:);
mean_d=data.output(24,:);
Le=data.output(25,:);
Re=data.output(26,:);


% % ipts = zeros(3,10,tfinal-ti+1);
% % est_ipts = zeros(3,10,tfinal-ti+1);

tf=length(time);

index=0;

for t=2:tf
    ft(t) = time(t)-time(t-1);
 
end

x_cum=cum_disp(1,:);
z_cum=cum_disp(2,:);
L_cum=cum_disp(3,:);
t_cum=cum_disp(4,:);

figure(1); 
plot(M(:,1),M(:,2),'x',x_cum,z_cum);
axis equal


% % exp_sL=sqrt(sum(sL.^2));
% % exp_sT=sqrt(sum(sT.^2));
% % % % dist_meas=sum(abs(avg_l2));
% % % % fprintf('Visual Odometry Results:\n')
% % % % fprintf('   dx= %3.2f cm\n',cum_x(tf));
% % % % fprintf('   dz= %3.2f cm\n',cum_z(tf));
% % % % fprintf('   l2= %3.2f cm\n', dist_meas);
% % % % fprintf('   dh= %3.2f rad (%2.1f deg)\n', cum_h(end),cum_h(end)*180/pi);  
% % fprintf('   # of frames w/o match= %u of %u (%2.1f%%)\n', misses(end)-1,tf,100*(misses(end)-1)/tf);
% % fprintf('   Average frame rate= %2.1ffps\n',length(ft)/sum(ft));
% % fprintf('   Average number of matches = %u (%2.1f%%)\n',round(mean(matches)),100*mean(matches./num_ipts));
% % fprintf('   Expected Error in L = %3.1fcm\n',exp_sL);
% % fprintf('   Expected Error in Theta = %3.4frad\n',exp_sT);
% % 
% % % % plot measured visodo
% % figure(1); clf; hold on
% % plot(cum_x_av(1),cum_z_av(1),'ko','LineWidth',2,'MarkerSize', 10,'MarkerFaceColor','g') % start
% % plot(cum_x_av(tf),cum_z_av(tf),'ko','LineWidth',2,'MarkerSize', 10,'MarkerFaceColor','k') %av stop
% % plot(cum_x_wL(tf),cum_z_wL(tf),'ko','LineWidth',2,'MarkerSize', 10,'MarkerFaceColor','b') %wL stop
% % plot(cum_x_wT(tf),cum_z_wT(tf),'ko','LineWidth',2,'MarkerSize', 10,'MarkerFaceColor','g') %wT stop
% % % % plot([cum_x(tf) cum_x(tf)-2*sin(cum_h(tf))],[cum_z(tf) cum_z(tf)+2*cos(cum_h(tf))],'r-','LineWidth',2)
% % for i=2:tf-1
% %     r = 1; % radius for vector lines
% % % %     plot([cum_x(i) cum_x(i)-r*sin(cum_h(i))],[cum_z(i) cum_z(i)+r*cos(cum_h(i))],'k-','LineWidth',1)
% %     if misses(i)==misses(i-1)
% %         plot(cum_x_av(i),cum_z_av(i),'k.')
% %         plot(cum_x_wL(i),cum_z_wL(i),'b.')
% %         plot(cum_x_wT(i),cum_z_wT(i),'g.')
% %     else
% %         plot(cum_x_av(i),cum_z_av(i),'rx','MarkerSize',12)
% %         plot(cum_x_wL(i),cum_z_wL(i),'rx','MarkerSize',12)
% %         plot(cum_x_wT(i),cum_z_wT(i),'rx','MarkerSize',12)
% %     end
% % end
% % % % plot(cum_x,cum_z,'g--') 
% % axis equal
% % hold off
% % xlabel('x (cm)'); ylabel('z (cm)');
% % legend('wT','av','wL')
% % 
% % 
% % % % save(robot_output,'-append')