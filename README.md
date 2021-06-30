# SymphonyDB: A Polygloty for Knowledge Graph Query Processing
This codebase is part of a research project to present SymphonyDB, a prototype based on the polygloty model of query processing which is a multi-database approach supported by a unified access layer that can analyze/translate individual Knowledge Graph (KG) queries just-in-time and match each to the combination of likely best-performing Data Management Systems (DMSs) using Virtuoso, Blazegraph, RDF-3X, and MongoDB that are currently included in our prototype.

# To replicate the results

 1) Clone the repository
 2) Download the Data Management Systems (download links below)
 3) Extract the downloaded files in the project folder
 4) Run *polygloty.sh* to replicate the results
 5) Ensure to run the *bash files* as a privileged user otherwise these scripts may not be allowed to clear the cache

# Benchmark Datasets

| Dataset  | Link |
| ------------- | ------------- |
| Allie                | https://zenodo.org/record/3709091/files/allie.nt?download=1  |
| Cellcycle            | https://zenodo.org/record/3709091/files/cellcycle.nt?download=1  |
| DrugBank             | https://zenodo.org/record/3709091/files/drugbank.nt?download=1  |
| LinkedSPL            | https://zenodo.org/record/3709091/files/linkedspl.nt?download=1  |
|Datasets in JSON   | https://zenodo.org/record/3709091/files/JSON%20%28MongoDB%29.tar.bz2?download=1  |


# Data Management Systems (datasets are loaded)
| Data Management Systems  | Link |
| ------------- | ------------- |
| Virtuoso                | https://zenodo.org/record/3709091/files/virf.tar.bz2?download=1 |
| Blazegraph              | https://zenodo.org/record/3709091/files/Blazegraph.tar.bz2?download=1 |
| RDF-3X                  |  https://zenodo.org/record/3709091/files/rdf3x-0.3.7.tar.bz2?download=1|
| MongoDB                 |https://zenodo.org/record/3709091/files/MongoDB.tar.bz2?download=1  |


### Complete Evaluation Results
Our complete evaluation results can be found [here](https://github.com/oursubmission/CKG/tree/master/Results)

# Authors
* Masoud Salehpour (University of Sydney)
* Joseph G. Davis  (University of Sydney)



