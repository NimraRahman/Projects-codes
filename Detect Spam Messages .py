import imaplib
import email
import webbrowser

# ask user for email and password
username = input("Enter your email address: ")
password = input("Enter your email password: ")

# create connection with email provider
if "gmail" in username:
    imap_host = "imap.gmail.com"
elif "yahoo" in username:
    imap_host = "imap.mail.yahoo.com"
elif "outlook" in username or "hotmail" in username:
    imap_host = "outlook.office365.com"
else:
    print("Email provider not supported")
    exit()

mail = imaplib.IMAP4_SSL(imap_host)
mail.login(username, password)

# select inbox
mail.select("inbox")

# search for spam messages
typ, data = mail.search(None, "UNSEEN", "SPAM")

if data[0]:
    spam_ids = data[0].split()
    print(f"Found {len(spam_ids)} spam messages:")
    for spam_id in spam_ids:
        typ, data = mail.fetch(spam_id, "(RFC822)")
        raw_email = data[0][1]
        email_message = email.message_from_bytes(raw_email)
        print(f"\nSubject: {email_message['Subject']}")
        print(f"From: {email_message['From']}")
        print(f"To: {email_message['To']}")
        print(f"Date: {email_message['Date']}")

    # ask user if they want to delete spam messages
    choice = input("\nDo you want to delete these messages? (y/n): ")
    if choice.lower() == "y":
        # delete all spam messages
        mail.store(" ".join(spam_ids), "+FLAGS", "\\Deleted")
        mail.expunge()
        print("Deleted spam messages")
    elif choice.lower() == "n":
        print("Spam messages not deleted")
    else:
        print("Invalid choice")
else:
    print("No spam messages found")

# close connection
mail.close()
mail.logout()

