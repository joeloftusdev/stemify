using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;
using System.Threading;
using System.IO;

namespace SpleeterUI
{
    public partial class MainWindow : System.Windows.Window
    {
        private System.Windows.Controls.ProgressBar progressBar;
        private int percentageComplete = 0;
        private TextBlock callbackMessage;
        private bool success = false;
        private static string dllPath = System.Configuration.ConfigurationManager.AppSettings["SpleeterLibPath"];
        private static string dllImportAttribute = $@"[DllImport(""{dllPath}"", CallingConvention = CallingConvention.Cdecl)]";
            
        public MainWindow()
        {
            InitializeComponent();
            progressBar = this.FindName("ProgressBar") as System.Windows.Controls.ProgressBar;
            callbackMessage = this.FindName("CallbackMessage") as TextBlock;
        }

        [UnmanagedFunctionPointer(CallingConvention.StdCall)]
        public delegate void CallbackDelegate(string message);


        [DllImport("SpleeterLib.dll", CallingConvention = CallingConvention.Cdecl)]  


        public static extern int fnSpleeterLibGenerateStems(string sourceFile, string targetDir, int numOfStems, CallbackDelegate callback);

        public  void MyCallbackFunction(string message)
        {          
            if (message.Equals("Initializing Spleeter", StringComparison.OrdinalIgnoreCase))
            {
                percentageComplete = 0;
            }
            else
            {
                percentageComplete += 25;
            }

            if (progressBar != null)
            {          
                Dispatcher.Invoke(() => progressBar.Value = percentageComplete);
                Dispatcher.Invoke(() => callbackMessage.Text = message);
            }             
        }

        struct StemsParams
        {
            public string sourceFile;
            public string targetDir;
            public int numOfStems;
        }

      
        private void SelectSrcFileClicked(object sender, RoutedEventArgs e)
        {
            var dialog = new Microsoft.Win32.OpenFileDialog();
            dialog.Filter = "Wav File (.wav)|*.wav"; 

            bool? result = dialog.ShowDialog();

            if (result == true)
            {
                string filename = dialog.FileName;
                this.SelectedFileTxtBox.Text = filename;
            }
        }

        private void SelectOutputDirClicked(object sender, RoutedEventArgs e)
        {
            var folderBrowser = new FolderBrowserDialog();
            { 
                folderBrowser.Description = "Select a Folder...";
                folderBrowser.RootFolder = Environment.SpecialFolder.MyComputer;

                DialogResult result = folderBrowser.ShowDialog();

                if (result == System.Windows.Forms.DialogResult.OK && !string.IsNullOrWhiteSpace(folderBrowser.SelectedPath))
                {
                    string folderPath = folderBrowser.SelectedPath;
                    this.SelectedOutputDirTxtBox.Text = folderPath;
                }
            }
        }
      
        private void StartBackgroundTask(StemsParams stemsParams)
        {
            
            int returnValue = fnSpleeterLibGenerateStems(stemsParams.sourceFile, stemsParams.targetDir, stemsParams.numOfStems, MyCallbackFunction);
            if (returnValue == 0)
            {
                this.success = true;
            }
            
        }

        private async void GenerateStemsClicked(object sender, RoutedEventArgs e)
        {
            progressBar.Value = 0;
            Percentage.Visibility = Visibility.Visible;
            string sourceFile = this.SelectedFileTxtBox.Text;
            string outputDir = this.SelectedOutputDirTxtBox.Text;
            ComboBoxItem item = (ComboBoxItem)this.NoStemsComboBox.SelectedItem;
            string numberStems = item.Content.ToString()!;
            int intNumberStems = int.Parse(numberStems);
            StemsParams stemsParams = new StemsParams();
            stemsParams.sourceFile = sourceFile;
            stemsParams.targetDir = outputDir;
            stemsParams.numOfStems = intNumberStems;
            GenerateStemsBtn.IsEnabled = false;
            await Task.Run(() => StartBackgroundTask(stemsParams));
            GenerateStemsBtn.IsEnabled = true;
            if (!success) {
                System.Windows.MessageBox.Show("Error unable to generate stems.");
            }
          
        }

    }

}
