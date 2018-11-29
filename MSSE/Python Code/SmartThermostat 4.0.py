import tkinter as tk
from tkinter import ttk
import time

class ST(tk.Tk):
    def __init__(self):
        tk.Tk.__init__(self)
        def DesireTempUp():
            self.InitialDisplayTemp = self.InitialDisplayTemp + 1
            self.DisplayTemp.configure(text=self.InitialDisplayTemp)
            self.InitialDesireTemp = self.InitialDisplayTemp
            self.RecordedTemp[(self.ws%3)*50+int(self.OdTpScale.get())] = self.InitialDesireTemp
            self.RecordedType[(self.ws%3)*50+int(self.OdTpScale.get())] = 'Preset'
        def DesireTempDown():
            self.InitialDisplayTemp = self.InitialDisplayTemp - 1
            self.DisplayTemp.configure(text=self.InitialDisplayTemp)
            self.InitialDesireTemp = self.InitialDisplayTemp
            self.RecordedTemp[(self.ws%3)*50+int(self.OdTpScale.get())] = self.InitialDesireTemp
            self.RecordedType[(self.ws%3)*50+int(self.OdTpScale.get())] = 'Preset'
        def CurrentTempUp():
            self.InitialCurrentTemp = self.InitialCurrentTemp + 1
            self.DisplayCurrentTemp.configure(text=self.InitialCurrentTemp)
        def CurrentTempDown():
            self.InitialCurrentTemp = self.InitialCurrentTemp - 1
            self.DisplayCurrentTemp.configure(text=self.InitialCurrentTemp)
        def HumanStatus():
            self.hs = self.hs+1
            if self.hs%2 == 0:
                self.HumanStatus.configure(text='At Home')
            if self.hs%2 == 1:
                self.HumanStatus.configure(text="Is Out")
        def WeatherStatus():
            self.ws = self.ws+1
            if self.ws%3 == 0:
                self.WeatherStatusLabel.configure(text='Sunny')
            if self.ws%3 == 1:
                self.WeatherStatusLabel.configure(text="Cloudy")
            if self.ws%3 == 2:
                self.WeatherStatusLabel.configure(text="Rainy/Snowy")
        self.UserInterface = ttk.LabelFrame(self, text='User Interface') 
        self.UserInterface.grid(row=0,column=0 ,columnspan = 3,sticky='W', padx=10, pady=10)
        self.UserInterface.propagate(0)
        self.DisplayLabel = ttk.Label(self.UserInterface, text='Display') 
        self.DisplayLabel.grid(row=1,column=1,sticky='W')
        self.CrownLabel = ttk.Label(self.UserInterface, text='Crown  ') 
        self.CrownLabel.grid(row=1,column=4,sticky='E')
        self.InitialDisplayTemp = 20
        self.InitialDesireTemp = self.InitialDisplayTemp
        self.DisplayTemp = ttk.Label(self.UserInterface,text=self.InitialDisplayTemp,width=5)
        self.DisplayTemp.grid(row=2,column=1)
        self.TempUnitLabel = ttk.Label(self.UserInterface, text='℃     ')
        self.TempUnitLabel.grid(row=2,column=2)
        self.TempUpButton = ttk.Button(self.UserInterface, text="▲", width=2,command = DesireTempUp)
        self.TempUpButton.grid(row=2, column=4,sticky='W')
        self.TempDownButton = ttk.Button(self.UserInterface, text="▼", width=2,command = DesireTempDown)
        self.TempDownButton.grid(row=2, column=4,sticky='E')
        self.Blank = ttk.Label(self.UserInterface, text=" ")  # 7
        self.Blank.grid(row=3, column=0,sticky='E')
################################################################################
        self.StateMachine = ttk.LabelFrame(self, text='StateMachine') 
        self.StateMachine.grid(row=1,column=0,sticky='W',padx=10 )
        self.CurrentTempLabel = ttk.Label(self.StateMachine, text="CurrentTemp:")
        self.CurrentTempLabel.grid(row=2, column=0,sticky='W',padx=10)
        self.InitialCurrentTemp = 20
        self.DisplayCurrentTemp = ttk.Label(self.StateMachine,text=self.InitialCurrentTemp,width=5)
        self.DisplayCurrentTemp.grid(row=3,column=0,sticky='W',padx=12)
        self.TempUnitLabelCurrent = ttk.Label(self.StateMachine, text='℃')
        self.TempUnitLabelCurrent.grid(row=3,column=0,sticky='W',padx=55)
        self.TempUpButtonCurrent = ttk.Button(self.StateMachine, text="▲", width=2,command = CurrentTempUp)
        self.TempUpButtonCurrent.grid(row=3, column=1,sticky='E')
        self.TempDownButtonCurrent = ttk.Button(self.StateMachine, text="▼", width=2,command = CurrentTempDown)
        self.TempDownButtonCurrent.grid(row=3, column=2,sticky='W')
        self.hs=0
        self.HumanStatusLabel = ttk.Label(self.StateMachine, text="Huamn Detection:", width=17)
        self.HumanStatusLabel.grid(row=4, column=0,columnspan = 3,sticky='W',padx=10)
        self.HumanStatus = ttk.Label(self.StateMachine, text="At Home", width=12) 
        self.HumanStatus.grid(row=5, column=1,sticky='W',columnspan = 3)
        self.HumanButton = ttk.Button(self.StateMachine, text="Human", width=10,command = HumanStatus)
        self.HumanButton.grid(row=5, column=0,sticky='W',padx=10)
        self.ws=0
        self.OnlineDataLabel = ttk.Label(self.StateMachine, text="Online Data:", width=17)
        self.OnlineDataLabel.grid(row=6, column=0,columnspan = 3,sticky='W',padx=10)
        self.WeatherButton = ttk.Button(self.StateMachine, text="Weather", width=10,command = WeatherStatus)
        self.WeatherButton.grid(row=7, column=0,sticky='W',padx=10)
        self.WeatherStatusLabel = ttk.Label(self.StateMachine, text="Sunny", width=12) 
        self.WeatherStatusLabel.grid(row=7, column=1,sticky='W',columnspan = 3)
        self.OutdoorTempLabel = ttk.Label(self.StateMachine, text="     OutdoorTemp:")
        self.OutdoorTempLabel.grid(row=8, column=0,sticky='W',padx=10)
        self.OdTpScale = tk.Scale(self.StateMachine, from_=-10, to=39,tickinterval=10,orient='horizontal',length=200)
        self.OdTpScale.grid(row=9, column=0,sticky='W',columnspan = 3,padx=10)
        self.RecordedTempLabel = ttk.Label(self.StateMachine, text="     RecordedTemp:", width=17)
        self.RecordedTempLabel.grid(row=10, column=0,columnspan = 3,sticky='W',padx=10)
        self.RecordedTemp = [20]*150
        self.RecordedType = ['None']*150
        self.RecordedTempDisplay = ttk.Label(self.StateMachine, text='     '+str(self.RecordedTemp[(self.ws%3)*50+int(self.OdTpScale.get())])+"  ℃    "+self.RecordedType[(self.ws%3)*50+int(self.OdTpScale.get())], width=23)
        self.RecordedTempDisplay.grid(row=11, column=0,columnspan = 3,sticky='W',padx=10)
        self.Blank2 = ttk.Label(self.StateMachine, text=' ') 
        self.Blank2.grid(row=12,column=0,sticky='W')
################################################################################
        self.Status = ttk.LabelFrame(self, text='Status') 
        self.Status.grid(row=2,column=0,sticky='W',padx=10 )
        self.DesireTemp = ttk.Label(self.Status, text='DesireTemp:') 
        self.DesireTemp.grid(row=7,column=0,sticky='W',padx=10 )
        self.DesireTempPara = ttk.Label(self.Status, text=str(self.RecordedTemp[(self.ws%3)*50+int(self.OdTpScale.get())])+"℃")
        self.DesireTempPara.grid(row=7,column=1,sticky='W',padx=10 )
        self.DevicesStatus = ttk.Label(self.Status, text='DevicesStatus:') 
        self.DevicesStatus.grid(row=8,column=0,sticky='W',padx=10 )
        self.DevicesStatusPara = ttk.Label(self.Status, text='Off') 
        self.DevicesStatusPara.grid(row=8,column=1,sticky='W',padx=10 )
        self.DevicesMode = ttk.Label(self.Status, text='DevicesMode:') 
        self.DevicesMode.grid(row=9,column=0,sticky='W',padx=10 )
        self.DevicesModePara = ttk.Label(self.Status, text='None') 
        self.DevicesModePara.grid(row=9,column=1,sticky='W',padx=10 )
################################################################################
        self.update_clock()
    def update_clock(self):
        now = time.strftime("%H:%M:%S" , time.gmtime())
        self.RecordedTempDisplay.configure(text='     '+str(self.RecordedTemp[(self.ws%3)*50+int(self.OdTpScale.get())])+"  ℃    "+self.RecordedType[(self.ws%3)*50+int(self.OdTpScale.get())])
        if self.RecordedType[(self.ws%3)*50+int(self.OdTpScale.get())]!='None':
            self.InitialDisplayTemp = self.RecordedTemp[(self.ws%3)*50+int(self.OdTpScale.get())]
        self.DisplayTemp.configure(text=self.InitialDisplayTemp)
        if self.hs%2 == 0:
            if self.InitialDisplayTemp>self.InitialCurrentTemp:
                self.DevicesStatusPara.configure(text='On')
                self.DevicesModePara.configure(text='Heat Up')
                self.InitialCurrentTemp = round(self.InitialCurrentTemp + 0.1,1)
                self.DisplayCurrentTemp.configure(text=self.InitialCurrentTemp)
                self.DesireTempPara.configure(text=str(self.InitialDisplayTemp)+" ℃")
            if self.InitialDisplayTemp<self.InitialCurrentTemp:
                self.DevicesStatusPara.configure(text='On')
                self.DevicesModePara.configure(text='Cool Down')
                self.InitialCurrentTemp = round(self.InitialCurrentTemp - 0.1,1)
                self.DisplayCurrentTemp.configure(text=self.InitialCurrentTemp)
                self.DesireTempPara.configure(text=str(self.InitialDisplayTemp)+" ℃")
            if self.InitialDisplayTemp==self.InitialCurrentTemp:
                self.DevicesStatusPara.configure(text='Off')
                self.DevicesModePara.configure(text='None')
                self.DesireTempPara.configure(text=str(self.InitialDisplayTemp)+" ℃")
        if self.hs%2 == 1:
            self.DevicesStatusPara.configure(text='Off')
            self.DevicesModePara.configure(text='None')
            self.DesireTempPara.configure(text=str(self.InitialDisplayTemp)+" ℃")
        # call this function again in one second
        self.after(1000, self.update_clock)

if __name__== "__main__":
    SmartThermostat = ST()
    SmartThermostat.wm_title('Smart Thermostat')
    SmartThermostat.resizable(width=False, height=False)
    SmartThermostat.mainloop()
