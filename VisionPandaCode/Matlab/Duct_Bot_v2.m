function varargout = Duct_Bot_v2(varargin)
% DUCT_BOT_V2 M-file for Duct_Bot_v2.fig
%      DUCT_BOT_V2, by itself, creates a new DUCT_BOT_V2 or raises the existing
%      singleton*.
%
%      H = DUCT_BOT_V2 returns the handle to a new DUCT_BOT_V2 or the handle to
%      the existing singleton*.
%
%      DUCT_BOT_V2('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in DUCT_BOT_V2.M with the given input arguments.
%
%      DUCT_BOT_V2('Property','Value',...) creates a new DUCT_BOT_V2 or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before Duct_Bot_v2_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to Duct_Bot_v2_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help Duct_Bot_v2

% Last Modified by GUIDE v2.5 08-Aug-2013 11:33:21

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @Duct_Bot_v2_OpeningFcn, ...
                   'gui_OutputFcn',  @Duct_Bot_v2_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before Duct_Bot_v2 is made visible.
function Duct_Bot_v2_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to Duct_Bot_v2 (see VARARGIN)

% Choose default command line output for Duct_Bot_v2
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

global IP;
global commsToolsPath;

IP = get(handles.IPaddress,'String');
assignin('base','IP',IP);
assignin('base','handles',handles);
commsToolsPath=regexprep(which('putty.exe'), 'putty.exe','');
assignin('base','commsToolsPath',commsToolsPath);


global MD;
MD = 0.3;

global S1;
global S2;
S1 = 0;
S2 = 0;
assignin('base','S1',S1);
assignin('base','S2',S2);

global MDLNAME;
MDLNAME = 'Duct_Bot_Motors';
assignin('base','MDLNAME',MDLNAME);

set(handles.Lspeed,'String',sprintf('%2.1f',S2));
set(handles.Rspeed,'String',sprintf('%2.1f',S1));
set(handles.botconnect,'Style','text');
set(handles.savefile,'Style','text');



% UIWAIT makes Duct_Bot_v2 wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = Duct_Bot_v2_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;

% --- Executes on button press in startvid.
function startvid_Callback(hObject, eventdata, handles)
% hObject    handle to startvid (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global IP;
global commsToolsPath;
global record;
global filename;

set(handles.filename,'Enable','inactive')
set(handles.storevidcheck,'Enable','inactive')

record = get(handles.storevidcheck,'value');

set(handles.startvid,'String',sprintf('\n Starting'));
set(handles.startvid,'BackgroundColor','y');
set(handles.startvid,'Style','text');

[status]=system([commsToolsPath,'plink -T -ssh -pw password root@',IP,' "ps cax | grep vlc"']);
while ~status
    [status,result]=system([commsToolsPath,'plink -ssh -pw password root@',IP,... % Opens plink for ssh communication with lnx target
							' "killall -9 vlc"']);
    [status]=system([commsToolsPath,'plink -T -ssh -pw password root@',IP,' "ps cax | grep vlc"']);
end

T = timer('Period',20.0);
set(T,'TimerFcn',['[status]=system([commsToolsPath,''plink -T -ssh -pw password root@'',IP,'' "ps cax | grep vlc"'']);',...
    'if ~status;'...
    'system(''taskkill /F /IM plinkvid.exe'');'...
    'end']);
set(T,'ExecutionMode','fixedRate');
start(T);

if record    
    filename=get(handles.filename,'String');
    assignin('base','filename',filename);
    [status,result]=system([commsToolsPath,'plinkvid -T -ssh -pw password wesley@',IP,... % Opens plink for ssh communication with lnx target
							' "cvlc --noaudio v4l2:///dev/video0 :v4l2-height=240 :v4l2-width=320 :live-caching=60 --sout ''#transcode{venc=x264{tune=zerolatency,intra-refresh}}:duplicate{dst=standard{access=file,mux=asf,dst=/home/wesley/',filename,'.asf},dst=standard{access=udp{ttl=1,caching=0,frame=100},mux=ts,dst=10.0.0.10:1234}}''"']);
else
    [status,result]=system([commsToolsPath,'plinkvid -T -ssh -pw password wesley@',IP,... % Opens plink for ssh communication with lnx target
							' "cvlc --noaudio v4l2:///dev/video0 :v4l2-height=240 :v4l2-width=320 :live-caching=60 --sout ''#transcode{venc=x264{tune=zerolatency,intra-refresh}}:duplicate{dst=standard{access=udp{ttl=1,caching=0,frame=100},mux=ts,dst=10.0.0.10:1234}}''"']);
end
    set(handles.startvid,'String',sprintf('\n Video Running'));
    set(handles.startvid,'BackgroundColor','g');

stop(T);
delete(T);
                        % set(handles.startvid,'String',sprintf('\n Video Started'));
% set(handles.startvid,'BackgroundColor','g');





                    
% --- Executes on button press in stopvid.
function stopvid_Callback(hObject, eventdata, handles)
% hObject    handle to stopvid (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global IP;
global commsToolsPath;
global record;

set(handles.stopvid,'String','Stopping Video');
set(handles.stopvid,'BackgroundColor','r');
[status,result]=system([commsToolsPath,'plink -ssh -pw password wesley@',IP,... % Opens plink for ssh communication with lnx target
							' "killall -9 vlc"']); 
set(handles.stopvid,'String','Stop Video on Target');
set(handles.stopvid,'BackgroundColor',[212/255,208/255,200/255]);
set(handles.startvid,'String','Start Video on Target');
set(handles.startvid,'BackgroundColor',[212/255,208/255,200/255]);
set(handles.startvid,'Style','pushbutton');
set(handles.filename,'Enable','on')
set(handles.storevidcheck,'Enable','on')

if record
    set(handles.savefile,'String','Save File to Desktop');
    set(handles.savefile,'Style','pushbutton');
end

                        
% --- Executes on button press in startstream.
function startstream_Callback(hObject, eventdata, handles)
% hObject    handle to startstream (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global vlc;
vlc=actxcontrol('VideoLAN.VLCPlugin.2',[25,75,320,240]);
vlc.playlist.add('udp://@:1234','webcam',':udp-caching=0');
vlc.playlist.play();
set(handles.startstream,'String','Playing');
set(handles.startstream,'BackgroundColor','g');



% --- Executes on button press in stopstream.
function stopstream_Callback(hObject, eventdata, handles)
% hObject    handle to stopstream (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global vlc
vlc.playlist.stop();
vlc.playlist.items.clear();
set(handles.startstream,'String','Start Stream');
set(handles.startstream,'BackgroundColor',[212/255,208/255,200/255]);


% --- Executes on button press in ForwardButton.
function ForwardButton_Callback(hObject, eventdata, handles)
% hObject    handle to ForwardButton (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global MD;
global MDLNAME;
global S1;
global S2;
S1 = S1+MD;
S2 = S2+MD;
assignin('base','S1',S1);
assignin('base','S2',S2);
set(handles.Lspeed,'String',sprintf('%2.1f',S2));
set(handles.Rspeed,'String',sprintf('%2.1f',S1));
set_param(MDLNAME,'SimulationCommand','Update');


% --- Executes on button press in ReverseButton.
function ReverseButton_Callback(hObject, eventdata, handles)
% hObject    handle to ReverseButton (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global MD;
global MDLNAME;
global S1;
global S2;
S1 = S1-MD;
S2 = S2-MD;
assignin('base','S1',S1);
assignin('base','S2',S2);
set(handles.Lspeed,'String',sprintf('%2.1f',S2));
set(handles.Rspeed,'String',sprintf('%2.1f',S1));
set_param(MDLNAME,'SimulationCommand','Update');


% --- Executes on button press in LeftButton.
function LeftButton_Callback(hObject, eventdata, handles)
% hObject    handle to LeftButton (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global MD;
global MDLNAME;
global S1;
global S2;
S1 = S1-MD;
S2 = S2+MD;
assignin('base','S1',S1);
assignin('base','S2',S2);
set(handles.Lspeed,'String',sprintf('%2.1f',S2));
set(handles.Rspeed,'String',sprintf('%2.1f',S1));
set_param(MDLNAME,'SimulationCommand','Update');



% --- Executes on button press in RightButton.
function RightButton_Callback(hObject, eventdata, handles)
% hObject    handle to RightButton (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global MD;
global MDLNAME;
global S1;
global S2;
S1 = S1+MD;
S2 = S2-MD;
assignin('base','S1',S1);
assignin('base','S2',S2);
set(handles.Lspeed,'String',sprintf('%2.1f',S2));
set(handles.Rspeed,'String',sprintf('%2.1f',S1));
set_param(MDLNAME,'SimulationCommand','Update');


% --- Executes on button press in StopButton.
function StopButton_Callback(hObject, eventdata, handles)
% hObject    handle to StopButton (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global MD;
global MDLNAME;
global S1;
global S2;
S1 = 0;
S2 = 0;
assignin('base','S1',S1);
assignin('base','S2',S2);
set(handles.Lspeed,'String',sprintf('%2.1f',S2));
set(handles.Rspeed,'String',sprintf('%2.1f',S1));
set_param(MDLNAME,'SimulationCommand','Update');


% --- Executes on button press in botcode.
function botcode_Callback(hObject, eventdata, handles)
% hObject    handle to botcode (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global MDLNAME;
global IP;
global commsToolsPath;

set(handles.botcode,'String',sprintf('\n Starting'));
set(handles.botcode,'BackgroundColor','y');
set(handles.botcode,'Style','text');

[status]=system([commsToolsPath,'plink -T -ssh -pw password root@',IP,' "ps cax | grep ',MDLNAME,'"']);
while ~status
    system([commsToolsPath,'plink -ssh -pw password root@',IP,... % Opens plink for ssh communication with lnx target
							' "killall -9 ',MDLNAME,'"']);
    [status]=system([commsToolsPath,'plink -T -ssh -pw password root@',IP,' "ps cax | grep ',MDLNAME,'"']);
end
T = timer('Period',20.0);
set(T,'TimerFcn',['[status]=system([commsToolsPath,''plink -T -ssh -pw password root@'',IP,'' "ps cax | grep '',MDLNAME,''"'']);',...
    'if ~status;'...
    'set(handles.botconnect,''String'',sprintf(''Connect to Bot''));'...
    'set(handles.botconnect,''Style'',''pushbutton'');'...
    'set(handles.botcode,''String'',sprintf(''\n Code Started''));'...
    'set(handles.botcode,''BackgroundColor'',''g'');'...
    'stop(timerfind);'...
    'delete(timerfind);'...
    'end']);
set(T,'ExecutionMode','fixedRate');
start(T);
[status,result]=system([commsToolsPath,'plinkbot -T -ssh -pw password root@',IP,... % Opens plink for ssh communication with lnx target
							' "/matlab_code/',MDLNAME,' -w"']);





% --- Executes on button press in botconnect.
function botconnect_Callback(hObject, eventdata, handles)
% hObject    handle to botconnect (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global MDLNAME;
global IP;
global commsToolsPath;

if strcmp(get(handles.botconnect,'String'),'Connect to Bot')
    load_system('C:\RTtools\VU-RLNX\RLNX\Duct_Bot_Motors.mdl');
    set_param(MDLNAME,'SimulationMode','external');
    set_param(MDLNAME,'SimulationCommand','connect');
    set_param(MDLNAME,'SimulationCommand','start');
    set(handles.botconnect,'String','Disconnect');
    set(handles.botconnect,'BackgroundColor','r');
else
    set(handles.botconnect,'String','');
    set(handles.botconnect,'Style','text');
    set(handles.botconnect,'BackgroundColor',[212/255,208/255,200/255]);
    set_param(MDLNAME,'SimulationCommand','stop');
    set_param(MDLNAME,'SimulationCommand','disconnect');
    [status,result]=system([commsToolsPath,'plink -ssh -pw password root@',IP,... % Opens plink for ssh communication with lnx target
							' "killall -9 ',MDLNAME,'"']);
    close_system(MDLNAME);
    set(handles.botcode,'String','Start Code on Bot');
    set(handles.botcode,'Style','pushbutton');
    set(handles.botcode,'BackgroundColor',[212/255,208/255,200/255]);
end





% --- Executes on key press with focus on figure1 or any of its controls.
function figure1_WindowKeyPressFcn(hObject, eventdata, handles)
% hObject    handle to figure1 (see GCBO)
% eventdata  structure with the following fields (see FIGURE)
%	Key: name of the key that was pressed, in lower case
%	Character: character interpretation of the key(s) that was pressed
%	Modifier: name(s) of the modifier key(s) (i.e., control, shift) pressed
% handles    structure with handles and user data (see GUIDATA)
global MD;
global MDLNAME;
global S1;
global S2;

press=double(get(gcf,'CurrentCharacter'));

if press == 28
    S1 = S1-MD;
    S2 = S2+MD;
    assignin('base','S1',S1);
    assignin('base','S2',S2);
    set(handles.Lspeed,'String',sprintf('%2.1f',S2));
    set(handles.Rspeed,'String',sprintf('%2.1f',S1));
    set_param(MDLNAME,'SimulationCommand','Update');
elseif press == 29
    S1 = S1+MD;
    S2 = S2-MD;
    assignin('base','S1',S1);
    assignin('base','S2',S2);
    set(handles.Lspeed,'String',sprintf('%2.1f',S2));
    set(handles.Rspeed,'String',sprintf('%2.1f',S1));
    set_param(MDLNAME,'SimulationCommand','Update');
elseif press == 30
    S1 = S1+MD;
    S2 = S2+MD;
    assignin('base','S1',S1);
    assignin('base','S2',S2);
    set(handles.Lspeed,'String',sprintf('%2.1f',S2));
    set(handles.Rspeed,'String',sprintf('%2.1f',S1));
    set_param(MDLNAME,'SimulationCommand','Update');
elseif press == 31
    S1 = S1-MD;
    S2 = S2-MD;
    assignin('base','S1',S1);
    assignin('base','S2',S2);
    set(handles.Lspeed,'String',sprintf('%2.1f',S2));
    set(handles.Rspeed,'String',sprintf('%2.1f',S1));
    set_param(MDLNAME,'SimulationCommand','Update');
elseif press == 32
    S1 = 0;
    S2 = 0;
    assignin('base','S1',S1);
    assignin('base','S2',S2);
    set(handles.Lspeed,'String',sprintf('%2.1f',S2));
    set(handles.Rspeed,'String',sprintf('%2.1f',S1));
    set_param(MDLNAME,'SimulationCommand','Update');
end



function IPaddress_Callback(hObject, eventdata, handles)
% hObject    handle to IPaddress (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of IPaddress as text
%        str2double(get(hObject,'String')) returns contents of IPaddress as a double
IP = get(handles.IPaddress,'String');
assignin('base','IP',IP);


% --- Executes during object creation, after setting all properties.
function IPaddress_CreateFcn(hObject, eventdata, handles)
% hObject    handle to IPaddress (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in pingbutton.
function pingbutton_Callback(hObject, eventdata, handles)
% hObject    handle to pingbutton (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global IP;
[status]=system(['ping -n 1 -w 30 ',IP]);
if status
    set(handles.checkconnect,'String','Not Connected');
    set(handles.checkconnect,'BackgroundColor','r');
elseif ~status
    set(handles.checkconnect,'String','Connected');
    set(handles.checkconnect,'BackgroundColor','g');
else
    set(handles.checkconnect,'String','Error');
    set(handles.checkconnect,'BackgroundColor','w');
end
    

    


% --- Executes on button press in storevidcheck.
function storevidcheck_Callback(hObject, eventdata, handles)
% hObject    handle to storevidcheck (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hint: get(hObject,'Value') returns toggle state of storevidcheck


function filename_Callback(hObject, eventdata, handles)
% hObject    handle to filename (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'String') returns contents of filename as text
%        str2double(get(hObject,'String')) returns contents of filename as a double


% --- Executes during object creation, after setting all properties.
function filename_CreateFcn(hObject, eventdata, handles)
% hObject    handle to filename (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: edit controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in savefile.
function savefile_Callback(hObject, eventdata, handles)
% hObject    handle to savefile (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
global commsToolsPath;
global filename;
global IP;
[status,result]=system([commsToolsPath,'pscp -scp -pw password root@',IP,... % Opens plink for ssh communication with lnx target
							':/home/wesley/',filename,'.asf "C:\Documents and Settings\gclayton\Desktop"']);
set(handles.savefile,'String','');
set(handles.savefile,'Style','text');
