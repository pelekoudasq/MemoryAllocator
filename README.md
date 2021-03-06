# Optimized Memory Allocator
### assignment for Operating Systems (F17/Κ22) Prof. Yannis Smaragdakis

#### Λειτουργικά Συστήματα, Κ22, Άσκηση 1
#### Πελεκούδας Ιωάννης, ΑΜ: 1115201500128

Ο παρών φάκελος περιέχει τα αρχεία allocator.c, allocator.h και ένα πρόγραμμα test.c για να ελέγχει τον allocator.
Το αρχείο πηγαίου κώδικα allocator.c περιέχει τις εξής συναρτήσεις:

τις κύριες συναρτήσεις που ξέρει και χρησιμοποιεί ο χρήστης
```C
void *mymalloc(size_t cbytes);
void myfree(void* address); 
```

αλλά και τις βοηθητικές:
```C
void newNodeDomis(Domi **L, int bit_vector_size, int klasi);
void allocateOneMegabyte();
void *lookForZero(Domi **L, int bit_vector_size, int klasi);
int ipow(int base, int exp);
```

Αναλυτικότερα, η συνάρτηση mymalloc ελέγχει το μέγεθος της μνήμης που αιτείται ο χρήστης όπως αναφέρεται στην εκφώνηση.
Αν cbytes > 4096, καλεί την παραδοσιακή malloc και επιστρέφει την διεύθυνση που επιστρέφει. 
Αν cbytes <= 4096, στρογγυλεύει τον αριθμό στην κοντινότερη μεγαλύτερη δύναμη του 2, που είναι τουλάχιστον 32 bytes,
άρα δημιουργει τις 8 τάξεις μεγέθους μεγέθους : 32, 64, 128, 256, 512, 1024, 2048, και 4096 bytes). 
Ήδη έχουν δημιουργηθεί μερικές global static μεταβλητές για την αρχή και το τέλος της δεξαμενής σελίδων,
ένα ευρετήριο για τις διάφορες τάξεις μεγέθους αλλά και το αρχικοποιημένο με NULL hashtable για την αποθήκευση των αρχών των σελίδων που θα δημιουργηθούν στη συνέχεια από την allocateOneMegabyte.
Πίσω στην mymalloc, αφού μπεί στο κατάλληλο if, αν το ευρετήριο της αντίστοιχης θέσης είναι κενό
–δηλαδή δεν έχει ξαναδεχθεί να δεσμέυσει μνήμη τέτοιας τάξης μέγέθους- τότε καλείται η συνάρτηση newNodeDomis, αλλιώς καλείται η lookForZero.

Η συνάρτηση newNodeDomis δημιουργεί καινούργιο κόμβο λίστας τύπου Domi (δείκτης σε char array, δείκτης σε μνήμη void *, δείκτης next Domi), 
αν έχει εξαντληθει η δεξαμενή σελιδων ή δεν έχει δημιουργηθεί καν, καλεί την allocateOneMegabyte. 
Στον δείκτη selida της δομής ανατίθεται ο δείκτης arxi της δεξαμενής, ο οποίος ύστερα μεγαλώνει κατά μια σελίδα.
Στη συνέχεια δημιουργεί char array μεγέθους bit_vector_size (προκύπτει από την πράξη 4096/κλάση/8, και ουσιαστικά δείχνει πόσοι χαρακτήρες θα χρειαστούν για το bitmap).
Το πρώτο bit του πρώτου χαρακτήρα αρχικοποιείται σε 1. O κόμβος αυτός συνδέεται στον pointer που δώθηκε ως όρισμα στην συνάρτηση. 
Τέλος, η αρχή της σελίδας που υποδεικνύει ο κόμβος,
αποθηκεύεται σε καινούργιο node του hashlist της κατάλληλης θέσης του hashtable σύμφωνα με την hashfunction που στην προκειμένη περίπτωση είναι η mod 8093. 
Προφανώς αν είναι η πρώτη κλήση της mymalloc, αρχικοποιείται και το hashtable νωρίτερα με NULL με την βοήθεια της calloc.

Η allocateOneMegabyte καλείται μόνο από την newNodeDomis, καθώς μόνο όταν δημιουργείται καινούργιος κόμβος δεσμεύεται σελίδα από την δεξαμενή.
Κάνει, λοιπόν, malloc 1MB στον global static δείκτη arxi, βάζει το telos να δείχνει 1MB μετά από τον δείκτη arxi.
Ύστερα, κόβεται το αρχικό μέρος της μνήμης αυτής μέχρι το πρώτο πολλαπλάσιο του 4096, και αντίστοιχα το τελευταίο.
Μετατίθονται τελικά και οι δείκτες arxi και telos ανάλογα.

Η συνάρτηση lookForZero ουσιαστικά καλείται από την στιγμή που το ευρετήριο δεν είναι κενό στην αντίστοιχη τάξη μεγέθους. 
Ψάχνει λοιπόν ένα node Domi, το bitmap του για την ακρίβεια, για κενή θέση (0). 
Αν δεν βρεί κάτι, καλεί αναδρομικά τον εαυτό της.
Αν καταλήξει ότι δεν υπάρχει άλλος κόμβος να ψάξει, τότε καλεί την newNodeDomis. 
Αν βρεί θέση, τότε επιστρέφει την αντίστοιχη θέση στην σελίδα και κάνει το αντίστοιχο bit 1. 
Να επισημανθεί πως στις τάξεις μεγέθους 1024, 2048 και 4096 που χρησιμοποιείται μισό, τέταρτο και όγδοο του χαρακτήρα αντίστοιχα, γίνεται κατάλληλο break με την βοήθεια counter.

Τέλος, κατά την υλοποίηση των lookForZero αλλά και της myfree (που ουσιαστικά κάνει την ανάστροφη διαδικασία), 
χρειάστηκε η ύψωση σε δύναμη ακεραίων με αποτέλεσμα ακέραιο.
Η βιβλιοθήκη math.h προσφέρει τέτοιες συναρτήσεις αλλά μόνο για ορίσματα float και double τύπους μεταβλητών.
Έτσι χρησιμοποιήθηκε η συνάρτηση ipow η οποία πάρθηκε αυτούσια από εδώ: https://stackoverflow.com/a/101613

