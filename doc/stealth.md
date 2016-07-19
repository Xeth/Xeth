##Stealth payments
Stealth payment is a private exchange of funds which protects the privacy of the recipient and prevents observers from knowing the user's transaction history.


On each payment the sender generates a new address using the recipient's stealth address data. 
Only the recipient is able to spend those funds. The spending private key can be generated only by the receiver.


##Dual-key stealth

Dual key allows scanning for payments without exposing the spending private key. 
In this scheme two keys are used - one for spending and one for scanning. The spending key is decrypted only when spending funds and it requires user interaction. 
The scan key is not encrypted.


Receiver:
```
Q = public scan key (EC point, 33 bytes)
d = private scan key (integer, 32 bytes)
R = public spend key
f = private spend key

Q = dG
R = fG

stealth address: <scan=Q> <spend=R, ...>
```

Sender (has Q, not d):

```
P = eG
```

By publishing P, only sender and receiver have access to c:
```
c = H(eQ) = H(dP)
```

Sender:
```
R' = R + cG
```

Receiver:
```
R' = R + cG     [without decrypting wallet]
   = (f + c)G   [after decryption of wallet]
```

In this scheme, we can use the scan keypair (Q, d) to generate the shared secret c, and then hence derive the address from the public part R. 


##Credits

The concept was invented by Peter Todd based on ByteCoin's earlier work.

