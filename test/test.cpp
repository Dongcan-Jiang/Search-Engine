int main() {
    const string INDEX_DIR = "index";
    vector<vector<string>> dataset = {
        {"doc1", "a b c d e f g"},
        {"doc2", "x a e c d"},
        {"doc3", "l x y t"},
        {"doc4", "k b r d w"},
        {"doc5", "u t w x a"},
        {"doc6", "m t a"}
    };
    index(INDEX_DIR, dataset);
    searchitem(INDEX_DIR, dataset, "a");
    return 0;
}
