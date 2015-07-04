function varargout = remote_control_gui(varargin)
% REMOTE_CONTROL_GUI M-file for remote_control_gui.fig
%      REMOTE_CONTROL_GUI, by itself, creates a new REMOTE_CONTROL_GUI or raises the existing
%      singleton*.
%
%      H = REMOTE_CONTROL_GUI returns the handle to a new REMOTE_CONTROL_GUI or the handle to
%      the existing singleton*.
%
%      REMOTE_CONTROL_GUI('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in REMOTE_CONTROL_GUI.M with the given input arguments.
%
%      REMOTE_CONTROL_GUI('Property','Value',...) creates a new REMOTE_CONTROL_GUI or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before remote_control_gui_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to remote_control_gui_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help remote_control_gui

% Last Modified by GUIDE v2.5 11-Jun-2013 11:08:15

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @remote_control_gui_OpeningFcn, ...
                   'gui_OutputFcn',  @remote_control_gui_OutputFcn, ...
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


% --- Executes just before remote_control_gui is made visible.
function remote_control_gui_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to remote_control_gui (see VARARGIN)

% Choose default command line output for remote_control_gui
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes remote_control_gui wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = remote_control_gui_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in forward.
function forward_Callback(hObject, eventdata, handles)
% hObject    handle to forward (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
assignin('base','L',0.6);
assignin('base','R',0.6);
set_param('adapt_visodo05_RC','SimulationCommand','update');

% --- Executes on button press in stop.
function stop_Callback(hObject, eventdata, handles)
% hObject    handle to stop (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
assignin('base','L',0);
assignin('base','R',0);
set_param('adapt_visodo05_RC','SimulationCommand','update');

% --- Executes on button press in left.
function left_Callback(hObject, eventdata, handles)
% hObject    handle to left (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
assignin('base','L',0.3);
assignin('base','R',0.9);
set_param('adapt_visodo05_RC','SimulationCommand','update');

% --- Executes on button press in right.
function right_Callback(hObject, eventdata, handles)
% hObject    handle to right (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
assignin('base','L',0.9);
assignin('base','R',0.3);
set_param('adapt_visodo05_RC','SimulationCommand','update');


% --- Executes on button press in terminate.
function terminate_Callback(hObject, eventdata, handles)
% hObject    handle to terminate (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set_param('adapt_visodo05_RC','SimulationCommand','stop');
