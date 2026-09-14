"""Execute in a new kernel using this interpreter; write output to ignored results."""
import os
from pathlib import Path
import sys
import nbformat
from nbclient import NotebookClient
from jupyter_client import KernelManager
root=Path(__file__).resolve().parents[2]
# A local kernel spec avoids changing ~/.local or the system Jupyter registry.
kernels=root/'profiling/results/jupyter/kernels/zfc-profile'
kernels.mkdir(parents=True,exist_ok=True)
import json
(kernels/'kernel.json').write_text(json.dumps({'argv':[sys.executable,'-m','ipykernel_launcher','-f','{connection_file}'],'display_name':'ZFC profiling','language':'python'}))
os.environ['JUPYTER_PATH']=str(kernels.parents[1])
os.environ['IPYTHONDIR']=str(root/'profiling/results/ipython')
os.environ['MPLCONFIGDIR']=str(root/'profiling/results/matplotlib')
nb=nbformat.read(root/'profiling/notebooks/zfc_ab_timing.ipynb',as_version=4)
NotebookClient(nb,timeout=180,kernel_name='zfc-profile',resources={'metadata':{'path':str(root)}}).execute()
nbformat.write(nb,root/'profiling/results/zfc_ab_timing.executed.ipynb')
print('Executed all cells in a fresh Jupyter kernel.')
